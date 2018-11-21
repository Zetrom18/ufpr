## script para extrair Dummy Features da base de digitos manuscritos
## As imagens sao normalizadas no tamanho indicado nas variavies X e Y
## Aprendizagem de Maquina, Prof. Luiz Eduardo S. Oliveira
##
##

import cv2
import os
import numpy as np
import random

winSize = (20,20)
blockSize = (10,10)
blockStride = (5,5)
cellSize = (10,10)
nbins = 9
derivAperture = 1
winSigma = -1.
histogramNormType = 0
L2HysThreshold = 0.2
gammaCorrection = 1
nlevels = 64
 
hog = cv2.HOGDescriptor(winSize,blockSize,blockStride,cellSize,nbins,derivAperture,winSigma,histogramNormType,L2HysThreshold,gammaCorrection,nlevels)

def load_images(path_images, fout):
    print ('Loading images...')
    archives = os.listdir(path_images)
    images = []
    errors = 0
    arq = open('knn-digits/digits/files.txt')
    lines = arq.readlines()
    print ('Extracting dummy features')
    for line in lines:
        aux = line.split('/')[1]
        image_name = aux.split(' ')[0]
        label = line.split(' ')[1]
        label = label.split('\n')
        
        for archive in archives:
            if archive == image_name:
                image = cv2.imread(path_images +'/'+ archive, 0)
                rawpixel(image, label[0], fout)
                # images.append((image, label))
                try:
                    images.append(hog.compute(image))
                except:
                    errors += 1
    print(images)

    print("Errors: "+str(errors))

    print ('Done. Take a look into features.txt')
    return images

#########################################################
# Usa o valor dos pixels como caracteristica
#
#########################################################
    
def rawpixel(image, label, fout):
    
    ## novas dimensoes
    X= 20
    Y= 10
    
    image = cv2.resize(image, (X,Y) )
    #cv2.imshow("image", image )
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    
    fout.write(str(label) +  " ")
    
    indice = 0
    for i in range(Y):
        #vet= []
        for j in range(X):
            if( image[i][j] > 128):
                v = 0
            else:
                v = 1   
            #vet.append(v)      
    
            fout.write(str(indice)+":"+str(v)+" ")
            indice = indice+1

    fout.write("\n")
            

if __name__ == "__main__":


    fout = open("features.txt","w")
    
    images = load_images('knn-digits/digits/data', fout)

    fout.close
    
        

