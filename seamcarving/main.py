from seamcarving import SeamCarver

import os


def image_resize_without_mask(filename_input, filename_output, new_height, new_width):
    obj = SeamCarver(filename_input, new_height, new_width)
    obj.save_result(filename_output)


def object_removal(filename_input, filename_output, filename_mask):
    obj = SeamCarver(filename_input, 0, 0, object_mask=filename_mask)
    obj.save_result(filename_output)


if __name__ == '__main__':

    folder_in = 'in'
    folder_out = 'out'

    filename_input = 'image.jpg'
    filename_output = 'image_result.jpg'
    new_height = 384
    new_width = 312

    input_image = os.path.join(folder_in, "images", filename_input)
    output_image = os.path.join(folder_out, "images", filename_output)

    image_resize_without_mask(input_image, output_image, new_height, new_width)
