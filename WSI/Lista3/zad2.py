import tensorflow as tf
import cv2
import glob
import numpy as np
import matplotlib.pyplot as plt

# Load the trained model
model = tf.keras.models.load_model('trained_model')

test_images_folder_path = 'my_test/*/*.png'
test_image_paths = glob.glob(test_images_folder_path)

# Load and preprocess your test images
for image_path in test_image_paths:
    img = cv2.imread(image_path)[:,:,0] 
    img = cv2.resize(img,(28 , 28))     
    img = np.invert(np.array([img]))
    prediction = model.predict(img) 
    print(f"This digit is probably a {np.argmax(prediction)}") 
    plt.imshow(img[0] , cmap = plt.cm.binary)
    plt.show()  