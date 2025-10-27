# COMP2211 
# 2023S
# Programming Assignment 2

import numpy as np

# Task 1
def contrast_stretch(x):
    """ Stretch the contrast of each individual images in the given data array.

    Parameters
    ------------
    x : np.ndarray
        Image data array
    Returns:
    -------------
    np.ndarray
        New image data arary with individually contrast-stretched images.
    """

    ### START YOUR CODE HERE
    ### END YOUR CODE HERE
    return x_enhanced

# Task 2
def rescale_01(x):
  """ Rescales the given image data array to range [0,1].

  Parameters
  ------------
  x : np.ndarray
      image data array

  Returns:
  -------------
  np.ndarray
      New image data arary re-scaled to range [0,1].
  """
  ### START YOUR CODE HERE
  ### END YOUR CODE HERE
  return x_01.astype(float)
  
# Task 7
def threshold(val_preds, thresh_value):
    """Threshold the given predicted mask array.

    Parameters
    ----------
    val_preds : np.ndarray
        Predicted segmentation array on validation data
    thresh_value : float

    Returns
    ----------
    np.ndarray
        Thresholded val_preds
    """
    ### START YOUR CODE HERE
    ### END YOUR CODE HERE
    return val_preds_thresh.astype(int)

# Task 8
def dice_coef(mask1, mask2):
    """Calculate the dice coeffecient score between two binary masks.

    Parameters
    ----------
    mask1 : np.ndarray
        binary mask that consists of either 0 or 1.
    mask2 : np.ndarray
        binary mask that consists of either 0 or 1.

    Returns
    ----------
    float
        dice coefficient between mask1 and mask2.
    """
    ### START YOUR CODE HERE
    ### END YOUR CODE HERE
    return dice_coef_score

# Task 9
def avg_dice(y_val, val_preds_thresh):
    """Calculates the average dice coefficient score across all thresholded predictions & label pair of the validation dataset.

    Parameters
    ----------
    y_val : np.ndarray
        Ground truth segmentation labels array of the validation dataset
    val_preds : np.ndarray
        Predicted segmentation masks array on the validation dataset

    Returns
    ----------
    float
        Average dice score coefficient. 
    """ 
    ### START YOUR CODE HERE
    ### END YOUR CODE HERE
    return average_dice
    


# if __name__ == '__main__':