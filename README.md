# IoT-Project-Group-8

<!-- Table of Contents -->

Table of Contents
  1. Project Overview 
  2. Source Code 
  3. Report Files
  
---------------------------------------------------------------------------------------------------------------------------------------------

1. Project Overview:  
For our project we created a simple web application, using Heroku to host the Django code, that allows users to turn on and off their lights. 
We used the NodeMCU/Arduino as our controller hub, which connects to our LED diode light. The user will enter our web app. From there they 
will be able to turn on/off the light or turn on automatic mode. Once the user changes the lights state, via web app toggle switch. The 
NodeMCU/Arduino then makes a GET request from the Heroku API to change the lights state from on/off.

2. Source Code: 
The source code for our project is located in two folders. Folder 1 (titled Arduino Code) is where all of our Arduino source code, which 
controls the Node MCU and lights. Folder 2 (titled Django API Code) is where all of the code related to our Django server and API.
        
3. Report Files: 
         The rest of the repository is comprised of project report files, including:
                      - Architectural Design Decisions.pdf
                      - Deployment Decisions.pdf
                      - Light Demo.MOV
                      - Project Design and Architecture.pdf
                      - UI TESTING & TEST CASES.pdf
          
