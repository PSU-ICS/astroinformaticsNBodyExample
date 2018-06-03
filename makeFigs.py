#!/usr/bin/python3

#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
# makeFigs.py
#
# Author: Adam W. Lavely
# Date: June 2018
# Contact: adam.lavely@psu.edu
#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#

#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
# Get the required modules
import numpy as np
import glob 
import matplotlib.pyplot as plt

#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
# Read the data in

# Prepare the data structures for keeping
xLocT=[]
yLocT=[]
zLocT=[]
velXT=[]
velYT=[]
velZT=[]
massT=[]
files=[]

# Read in data for each file
fileName='/storage/home/awl5173/work/iAsk/astroClass/*.txt'
for nowFile in sorted(glob.glob(fileName)):

    # Get the data for that file
    xLoc,yLoc,zLoc,velX,velY,velZ,mass = np.loadtxt(nowFile,unpack=True)

    # Sort it into the data for us to keep    
    xLocT.append(xLoc)
    yLocT.append(yLoc)
    zLocT.append(zLoc)
    
    velXT.append(velX)
    velYT.append(velY)
    velZT.append(velZ)

    massT.append(mass)
    files.append(nowFile)

#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
# Do some data prep work

# Make into arrays for ease of use
xLocT=np.array(xLocT)
yLocT=np.array(yLocT)
zLocT=np.array(zLocT)

velXT=np.array(velXT)
velYT=np.array(velYT)
velZT=np.array(velZT)

massT=np.array(massT)

# Find the min and max values (to make plots that show all the data)
xlMax=np.max(xLocT)
ylMax=np.max(yLocT)
zlMax=np.max(zLocT)

xlMin=np.min(xLocT)
ylMin=np.min(yLocT)
zlMin=np.min(zLocT)

massMax=np.max(massT)
massMin=np.min(massT)

dotMax=50
dotMin=5

slope=(dotMax-dotMin)/(massMax-massMin)


#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
# Make the plots

for fcount in range(len(files)):
    
    # Create the plot
    plt.subplot(111)
    plt.scatter(xLocT[fcount],yLocT[fcount],s=5+slope*(massT[fcount]-massMin) )

    # Format the plot
    plt.xlim([xlMin-0.1*(xlMax-xlMin),xlMax+0.1*(xlMax-xlMin)])
    plt.ylim([ylMin-0.1*(ylMax-ylMin),ylMax+0.1*(ylMax-ylMin)])
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.tight_layout()
    #plt.axis('equal')

    # Save and close
    namer='figure'+str(fcount).zfill(5)+'.png'
    plt.savefig(namer)
    
    plt.axis('equal')
    namer='figureB'+str(fcount).zfill(5)+'.png'
    plt.savefig(namer)

    plt.close()

