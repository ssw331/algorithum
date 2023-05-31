# seam-carving

[![standard-readme compliant](https://img.shields.io/badge/standard--readme-OK-green.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

​		通过动态规划寻找能量图中能量最小的路径，删除该路径上的像素以缩放图像且不损失过多图像信息。
​		能量的定义有许多，在本项目中使用了较为简单的定义方式——梯度定义：
$$
e(x,y)=|\frac{\partial}{\partial x}I|+|\frac{\partial}{\partial y}I|
$$
​		即在(x,y)坐标处计算该像素在x轴、y轴方向上的偏导数，该处的能量为两个偏导数之和。

​		本项目中利用opencv的软件包直接实现单个图像的能量图计算。而对于本项目中能量最小的路径的寻路算法，则使用动态规划算法实现，其递推方程为：
$$
Min_e(x,y)=e(x,y)+min(Min_e(x-1,y-1),Min_e(x,y-1),Min_e(x+1,y-1))
$$


## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Maintainers](#maintainers)
- [License](#license)

## Install

​		本项目需要的环境依赖有cv2、numpy。若本地未安装这些环境依赖，可运行以下指令：

```powershell
pip install cv2
pip install numpy
```

## Usage

​		在运行本项目前请检查main.py文件中的下列参数：

```python
    folder_in = 'in'  # 输入文件文件夹名称
    folder_out = 'out'  # 输出文件文件夹名称

    filename_input = 'image.jpg'  # 输入图像文件名
    filename_output = 'image_result.jpg'  # 输出图像文件名
    new_height = 384  # 输出图像高度，请保持此高度与输入图像高度相同
    new_width = 312  # 输出图像宽度，请保证此值小于输入图像的宽度
```

​		folder_in为同级目录下输入图像存放的文件夹名称；
​		folder_out为同级目录下输出图像存放的文件夹名称；
​		filename_input为指定查找folder_in文件夹下的输入图像的名称；
​		filename_output为指定在folder_out文件夹下创建的输出图像的名称；
​		new_height为输出图像高度，由于本项目没有对高度压缩进行处理，因此请保持此高度与输入图像高度相同；
​		new_width为输出图像宽度，请保证此值小于输入图像的宽度。

​		参数调整完毕后，运行main.py文件，运行结束后会在指定文件夹内生成输出图像。

## 原图像

![image](C:\Users\24053\Desktop\大学\2022-2023学年第二学期\algorithm\2153877_唐书涵_Assignment4\code1\image.jpg)

## 运行结果

![image_result](C:\Users\24053\Desktop\大学\2022-2023学年第二学期\algorithm\2153877_唐书涵_Assignment4\code1\image_result.jpg)

## 时间复杂度

```python
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
```

​		basic operation为compare，而本算法中每次循环都会进行比较。因此动态规划的时间复杂度如下（考虑到实际中width>>2）：
$$
T_{dynamic}=height * width=\Theta{(height*width)}
$$
​		在此之外，本算法还有另外四个基本代码段，算法总体的时间复杂度如下：
$$
T_{total}=(3+height * width+2*height)*\Delta{pixels}=\Theta{(height*width*\Delta{pixels})}
$$


## 空间复杂度

​		本算法中，为了保存计算所得的最小能量，额外开辟了一个height*width大小的数组Min和大小为height的数组road。同时还有能量图energy_map和输出用数组output。

​		因此动态规划算法的空间复杂度为：
$$
S_{dynamic}=height*width=\Theta{(height*width)}
$$


​		总算法的空间复杂度为：
$$
S_{total}=3*height*width + height=\Theta{(height*width)}
$$


## Maintainers

[@ssw331](https://github.com/ssw331)

## License

MIT © 2023 ssw331
