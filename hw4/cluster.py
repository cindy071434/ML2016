import numpy as np
import sys
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.decomposition import PCA
from sklearn.decomposition import TruncatedSVD
from sklearn.cluster import KMeans, MiniBatchKMeans
from sklearn.feature_extraction import text 
from sklearn.preprocessing import Normalizer
from sklearn.pipeline import make_pipeline

dirr=str(sys.argv[1])
outt=str(sys.argv[2])

f = open('title.txt','r')
data = []
for line in f:
	data.append(line.strip())
f.close()


f = open('stopword.txt','r')
text = []
for line in f:
        text.append(line.strip())
f.close()


mystop = {'doesn','don','won','isn','aren','re','shouldn'}
stop = mystop.union(text)


TFIDFvectorizer = TfidfVectorizer(stop_words = stop, min_df = 0.00001)
x = TFIDFvectorizer.fit_transform(data)



svd = TruncatedSVD(n_components=20)
normalizer = Normalizer(copy=False)
lsa = make_pipeline(svd, normalizer)

U = lsa.fit_transform(x)


kmeans = KMeans(n_clusters=20)
kmeans.fit(U)

label = kmeans.labels_

f = open(dirr+'check_index.csv','r')
index = []
for line in f:
	index.append(line.strip().split(','))
f.close()

fout = open(outt,'w')
fout.write('ID,Ans\n')
for i in range(5000000):
	fout.write(str(i)+',')
	#print index[i+1]
	if label[int(index[i+1][1])] == label[int(index[i+1][2])]:
		fout.write(str(1)+'\n')
	else:
		fout.write(str(0)+'\n')



fout = open('count.csv','w')
data = []
for i in range(20000):
	if label[i]<10:
		fout.write(' '+str(label[i]))
	else:
		fout.write(str(label[i]))
	fout.write('\n')
f.close()
