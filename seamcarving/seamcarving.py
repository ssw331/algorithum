import numpy as np
import cv2


class SeamCarver:
    def __init__(self, filename, out_height, out_width, protect_mask='', object_mask=''):
        self.filename = filename
        self.out_height = out_height
        self.out_width = out_width

        self.in_image = cv2.imread(filename).astype(np.float64)
        self.in_height, self.in_width = self.in_image.shape[:2]  # 提取shape数组的前两个元素

        self.out_image = np.copy(self.in_image)

        # 以下为物体识别的相关属性设置
        self.object = (object_mask != '')
        if self.object:
            self.mask = cv2.imread(object_mask, 0).astype(np.float64)
            self.protect = False
        else:
            self.protect = (protect_mask != '')
            if self.protect:
                self.mask = cv2.imread(protect_mask, 0).astype(np.float64)

        # 卷积核 但本次实现没有使用 是原代码的残留
        self.kernel_x = np.array([[0., 0., 0.], [-1., 0., 1.], [0., 0., 0.]], dtype=np.float64)
        self.kernel_y_left = np.array([[0., 0., 0.], [0., 0., 1.], [0., -1., 0.]], dtype=np.float64)
        self.kernel_y_right = np.array([[0., 0., 0.], [1., 0., 0.], [0., -1., 0.]], dtype=np.float64)

        self.constant = 1000

        self.start()

    def start(self):
        self.seam_carving()

    def seam_carving(self):
        delta_height, delta_width = int(self.in_height - self.out_height), int(self.in_width - self.out_width)

        if delta_width > 0:
            self.seam_removal(delta_width)
        else:
            print("new_width大于原width，请重新调整new_width。")

        if delta_height != 0:
            print("new_height与原height不同，请调整为%d" % self.in_height)

    def seam_removal(self, num_pixels):
        for i in range(num_pixels):
            energy_map = self.cal_energy_map()
            cumulated_min_map = self.cumulating_min_map(energy_map)
            seam_idx = self.find_road(cumulated_min_map)
            self.delete_seam(seam_idx)

    def cal_energy_map(self):
        """计算能量图"""
        r, g, b = cv2.split(self.out_image)
        r_energy = np.absolute(cv2.Scharr(r, -1, 1, 0)) + np.absolute(cv2.Scharr(r, -1, 0, 1))
        g_energy = np.absolute(cv2.Scharr(g, -1, 1, 0)) + np.absolute(cv2.Scharr(g, -1, 0, 1))
        b_energy = np.absolute(cv2.Scharr(b, -1, 1, 0)) + np.absolute(cv2.Scharr(b, -1, 0, 1))
        return r_energy + g_energy + b_energy  # 返回的数组为二维数组，H*W = out_image‘s H*W

    def cumulating_min_map(self, energy_map):
        """动态规划计算能量最小的seam"""
        row, col = energy_map.shape
        Min = np.copy(energy_map)
        for i in range(1, row):
            for j in range(col):
                if j == 0:
                    Min[i, j] = energy_map[i, j] + min(Min[i - 1, j], Min[i - 1, j + 1])
                elif j == col - 1:
                    Min[i, j] = energy_map[i, j] + min(Min[i - 1, j - 1], Min[i - 1, j])
                else:
                    Min[i, j] = energy_map[i, j] + min(Min[i - 1, j - 1], Min[i - 1, j], Min[i - 1, j + 1])

        return Min

    def find_road(self, cumulated_min_map):
        row, col = cumulated_min_map.shape
        road = np.zeros(row, dtype=np.int32)
        road[-1] = np.argmin(cumulated_min_map[-1])
        for i in range(row - 2, -1, -1):
            p_x = road[i + 1]
            road[i] = np.argmin(cumulated_min_map[i, (p_x - 1 if p_x > 0 else 0):min(col - 1, p_x + 1)])
        return road

    def delete_seam(self, seam_idx):
        m, n = self.out_image.shape[: 2]
        output = np.zeros((m, n - 1, 3))
        for row in range(m):
            col = seam_idx[row]
            output[row, :, 0] = np.delete(self.out_image[row, :, 0], [col])
            output[row, :, 1] = np.delete(self.out_image[row, :, 1], [col])
            output[row, :, 2] = np.delete(self.out_image[row, :, 2], [col])
        self.out_image = np.copy(output)

    def save_result(self, filename):
        cv2.imwrite(filename, self.out_image.astype(np.uint8))
