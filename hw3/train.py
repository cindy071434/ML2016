import pickle
import numpy as np
import sys
import csv
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation,Reshape
from keras.layers.normalization import BatchNormalization
from keras.layers.advanced_activations import PReLU
from keras.utils import np_utils, generic_utils
from keras.optimizers import SGD
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.optimizers import SGD, Adadelta, Adagrad
from keras.layers import Input
from keras.models import Model

from keras.layers import Input, Dense
from keras.models import Model
from keras import backend as K
K.set_image_dim_ordering('th')


def rmse(predictions, targets):
    return np.sqrt(((predictions - targets) ** 2).mean())

s=sys.argv[1]

x_train = pickle.load(open(s+'all_label.p','rb'))
x_test = pickle.load(open(s+'all_unlabel.p','rb'))

x_train = np.reshape(np.array(x_train),(5000,3072));
x_test = np.reshape(np.array(x_test),(45000,3072));


x_train = x_train.astype('float32') / 255.
x_test = x_test.astype('float32') / 255.


classes=np.zeros((50000,10))



for i in range(45000):
	temp=np.zeros((10))
	c=0
	temp=1000000000000
	for j in range(5000):
		if rmse(x_train[j],x_test[i]) < temp:
			temp=rmse(x_train[j],x_test[i])
			c=j

	classes[i+5000][int(c/500)]=1



x_test=np.vstack((x_train,x_test))
for i in range (10):
        for j in range(500):
                classes[i*500+j][i]=1

x_test=np.reshape(x_test,(50000,3,32,32))

# x_test classes
model=Sequential()
model.add(Convolution2D(16, 3, 3, input_shape=(3,32, 32)))
model.add(Activation('relu'))
model.add(Convolution2D(32, 3, 3))
model.add(Activation('relu'))
model.add(MaxPooling2D((2,2)))
model.add(Dropout(0.3))
model.add(Convolution2D(64, 3, 3))
model.add(Activation('relu'))
model.add(Convolution2D(64, 3, 3))
model.add(Activation('relu'))
model.add(MaxPooling2D((2,2)))
model.add(Dropout(0.3))
model.add(Flatten())
model.add(Dense(output_dim=256))
model.add(Activation('relu'))
model.add(Dropout(0.3))
model.add(Dense(output_dim=10))
model.add(Activation('softmax'))
model.compile(loss='categorical_crossentropy',optimizer='Adadelta',metrics=['accuracy'])

for m in range(15):
	model.fit(x_test,classes,batch_size=100,nb_epoch=5)
	score=model.evaluate(x_test,classes)
	print('loss = ',score[0])
	print('acc = ',score[1])

model.save(sys.argv[2])

