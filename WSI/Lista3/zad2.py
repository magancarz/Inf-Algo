import tensorflow as tf
import cv2
import glob
import numpy as np

# Load the trained model
model = tf.keras.models.load_model('trained_model')

test_images_folder_path = 'my_test/*/*.png'
test_image_paths = glob.glob(test_images_folder_path)

# Load and preprocess your test images
for image_path in test_image_paths:
    img = cv2.imread(image_path)[:,:,0] 
    img = cv2.resize(img, (28, 28))     
    img = np.invert(np.array([img]))
    prediction = model.predict(img)
    print(f"Predicting {image_path}")
    print(f"This digit is probably a {np.argmax(prediction)}\n")