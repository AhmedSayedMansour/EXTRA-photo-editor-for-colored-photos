// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];

void loadImage ();
void saveImage ();
void blackandwhite ();
void invertimage ();
void mergeimage ();
void flipimage();
void rotateimage ();
void darkenandlightenimage ();
void detectimageedges ();
void enlargeimage ();
void shrinkimage ();

int main()
{
    char choose;
    cout<<"Ahalan ya user ya habibi\n";
    loadImage ();
    while(true){
    cout<<"Please select a filter to apply or 0 to exit:\n\n";
    cout<<"1-Black and White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Filter\n5-Rotate Image";
    cout<<"\n6-Darken and Lighten Image\n7-Detect Image Edges\n8-Enlarge Image";
    cout<<"\n9-Shrink Image\ns-Save the image to a file\n0-EXIT\nchoose :";
    cin>>choose;
    switch(choose){
        case '1':
            blackandwhite();
            break;
        case '2':
            invertimage ();
            break;
        case '3':
            mergeimage ();
            break;
        case '4':
            flipimage();
            break;
        case '5':
            rotateimage ();
            break;
        case '6':
            darkenandlightenimage ();
            break;
        case '7':
            detectimageedges ();
            break;
        case '8':
            enlargeimage ();
            break;
        case '9':
            shrinkimage() ;
            break;
        case 's':
            saveImage();
            break;
        case '0':
            return 0;
    }
    cout<<endl<<"photo saved successfully"<<endl;
    }
    return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
}

//_________________________________________
void blackandwhite() {
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++){
            for (int k = 0; k< RGB; k++){
            if (image[i][j][(RGB/3)-k]<=127.5)
                image[i][j][RGB-k]=0;
            else
               image[i][j][RGB-k]=255;
            }
        }
    }
}

void invertimage (){
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            for (int c=0;c<3;++c)
                image[i][j][c] = 255 - image[i][j][c];
        }
    }
}

void mergeimage (){
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
                for(int g= 0 ;g<RGB;g++){
            image2[i][j][g] = image[i][j][g];}
        }
    }
    cout <<"Enter the file name of the second photo\n";
    loadImage();
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            for(int g = 0 ;g<RGB;g++){
            image[i][j][g] = (image2[i][j][g]+image[i][j][g])/2;}
        }
    }
}

void flipimage(){
    char choose4;
    cout<<"Flip (h)orizontally or (v)ertically : ";
    cin>>choose4;
    if(choose4=='h'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++){
                swap(image[i][j],image[i][(SIZE-1)-j]);
            }
        }
    }
    else if(choose4=='v'){
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j< SIZE; j++){
                swap(image[i][j], image[(SIZE - 1) - i][j]);
            }
        }
    }
    else    cout<<"ERROR INVALID CHOOSE";
}

void rotateimage (){
    int choose5;
    for (int i = 0; i < (SIZE); i++){
        for (int j =i+1; j< (SIZE); j++) {
            swap(image[i][j],image[j][i]);
        }
    }
    cout<<"Rotate (90), (180) or (270) degrees : ";
    cin>>choose5;
    if(choose5==90){
        for (int i = 0; i < SIZE; i++ ){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[j][i], image[SIZE-j-1][i]);
            }
        }
    }
    else if(choose5==180){
        for (int i = 0; i < (SIZE); i++){
            for (int j =0; j< (SIZE-i); j++){
            swap(image[i][j],image[SIZE-j-1][SIZE-i-1]);
            }
        }
    }
    else if(choose5==270){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[i][j], image[i][SIZE-j-1]);
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void darkenandlightenimage (){
    char choose6;
    cout<<"Do you want to (d)arken or (l)ighten :";
    cin>>choose6;
    if(choose6=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for (int c=0;c<3;++c)
                    image[i][j][c] /=2;
            }
        }
    }
    else if(choose6=='l'){
        int num=0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for (int c=0;c<3;++c){
                    num=image[i][j][c]*2;
                    if (num>255)    num=255;
                    image[i][j][c]=num;
                }
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void detectimageedges (){
    for (int i=0; i<SIZE-1; i++) {
        for (int j=0; j<SIZE-1; j++) {
            if (abs(image[i][j][0] - image[i][j + 1][0] >= 30) || abs(image[i][j][0] - image[i + 1][j][0] >= 30))
				image[i][j][0] = 0;
			else    image[i][j][0] = 255;

			if (abs(image[i][j][1] - image[i][j + 1][1] >= 30) || abs(image[i][j][1] - image[i + 1][j][1] >= 30))
				image[i][j][1] = 0;
			else    image[i][j][1] = 255;

			if (abs(image[i][j][2] - image[i][j + 1][2] >= 30) || abs(image[i][j][2] - image[i + 1][j][2] >= 30))
				image[i][j][2] = 0;
			else    image[i][j][2] = 255;
        }
    }
}

void enlargeimage (){
    int choose8;
    cout<<"Which quarter to enlarge 1, 2, 3 or 4 : ";
    cin>>choose8;
    if(choose8==1){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j =0 ; j <(SIZE/2); j++) {
                for(int g=0;g<RGB;g++){
                    image2[i*2][j*2][g]=image[i][j][g];
                    image2[(i*2)+1][(j*2)][g]=image[i][j][g];
                    image2[(i*2)][(j*2)+1][g]=image[i][j][g];
                    image2[(i*2)+1][(j*2)+1][g]=image[i][j][g];
                }
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                for(int g=0;g<RGB;g++)
                    image[i][j][g]=image2[i][j][g];
            }
        }
    }
    else if(choose8==2){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j =0 ; j <(SIZE/2); j++) {
                for(int g=0;g<RGB;g++){
                    image2[i*2][j*2][g]=image[i][j+128][g];
                    image2[(i*2)+1][(j*2)][g]=image[i][j+128][g];
                    image2[(i*2)][(j*2)+1][g]=image[i][j+128][g];
                    image2[(i*2)+1][(j*2)+1][g]=image[i][j+128][g];
                }
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                for(int g=0;g<RGB;g++)
                    image[i][j][g]=image2[i][j][g];
            }
        }
    }
    else if(choose8==3){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j =0 ; j <(SIZE/2); j++) {
                for(int g=0;g<RGB;g++){
                    image2[i*2][j*2][g]=image[i+128][j][g];
                    image2[(i*2)+1][(j*2)][g]=image[i+128][j][g];
                    image2[(i*2)][(j*2)+1][g]=image[i+128][j][g];
                    image2[(i*2)+1][(j*2)+1][g]=image[i+128][j][g];
                }
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                for(int g=0;g<RGB;g++)
                    image[i][j][g]=image2[i][j][g];
            }
        }
    }
    else if(choose8==4){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j =0 ; j <(SIZE/2); j++) {
                for(int g=0;g<RGB;g++){
                    image2[i*2][j*2][g]=image[i+128][j+128][g];
                    image2[(i*2)+1][(j*2)][g]=image[i+128][j+128][g];
                    image2[(i*2)][(j*2)+1][g]=image[i+128][j+128][g];
                    image2[(i*2)+1][(j*2)+1][g]=image[i+128][j+128][g];
                }
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                for(int g=0;g<RGB;g++)
                    image[i][j][g]=image2[i][j][g];
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void shrinkimage (){
    float choose9;
    cout<<"1-Shrink to (1/2)\n2-Shrink to (1/3) \n3-Shrink to (1/4) \nchoose :";
    cin>>choose9;
    if (choose9==1){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                for (int c=0 ; c<RGB ; c++){
                image[i/2][j/2][c]=image[i][j][c];
                }
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/2 ; j <SIZE; j++){
                    for (int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
        for (int i = SIZE/2; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                    for(int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
    }
    if (choose9==2){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                for (int c=0 ; c<RGB ; c++){
                image[i/3][j/3][c]=image[i][j][c];
                }
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/3 ; j <SIZE; j++){
                    for (int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
        for (int i = SIZE/3; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                    for(int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
    }
    if (choose9==3){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                for (int c=0 ; c<RGB ; c++){
                image[i/4][j/4][c]=image[i][j][c];
                }
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/4 ; j <SIZE; j++){
                    for (int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
        for (int i = SIZE/4; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                    for(int c=RGB/255 ; c<RGB ; c++){
                image[i][j][c]=255;
                    }
            }
        }
    }
}
