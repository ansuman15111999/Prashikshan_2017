import processing.serial.*;

Serial myPort;

int start=10;
int stopa=11;
int backward=5;
int forward=4;
int left=2;
int right=3;

int count=0;
 


/* Creats six buttons and when we click on it , shows the fuction of button*/

int positionX, positionY;          // Position of circle button and other buttons w.r.t it
int rectSize = 40;             // Diameter of rect
int circleSize = 40;           // Diameter of circle

color rectColor, circleColor; //shows normal buttons when cursor is not over the button
color lightRect, lightCircle;// highlight buttons when cursor is over it

int textX=400;             // position of the text 
int textY=50;


boolean rectClicked1 = false; // this booleans checks weather the cursor is on the button or not
boolean rectClicked2 = false; // intially these are set to false i.e. not highlighted
boolean rectClicked3 = false; // when cursor come over any button its value changes from false to true due to code
boolean rectClicked4 = false;

boolean circleClicked1 = false;
boolean circleClicked2 = false;













void setup() {
  myPort=new  Serial(this,"COM8",9600);
  myPort.bufferUntil('\n');
   
  size(900, 700);
  rectColor = color(0);  // color of square button in normal
  lightRect = color(100); // color of square button when cursor is above it
  
  circleColor = color(0,255,0); // color of circular button in normal
  lightCircle = color(0,200,0); // color of circular button when cursor is above it
  
  
  background(255);
  positionX = width-200;
  positionY = height-110;

  rectMode(CENTER);
}

void draw() {
  
  update(mouseX, mouseY); // goes to user defined function update and give the mouseX and mouseY value     
 drawer();
                                // ##################################################*************(Please see the update funtion BELOW)
   
      
  if (circleClicked1) {             // completing UPDATE function it comes to here We have circleClicked1 TRUE SO it entres into loop
    fill(lightCircle);              //fills the lightcolor to circle ******* if We PRESSE mouse button at that Positon 
  } else {                                                              // goes to mousePreesed()    $$$$$$$$$$$$ GO DOWN
    fill(circleColor);
  }
  ellipse(positionX, positionY, circleSize, circleSize);
  
   
   if (circleClicked2) {           
    fill(lightCircle);
  } else {
    fill(circleColor);
  }
  ellipse(positionX+60, positionY, circleSize, circleSize);
     
     stroke(255);
   
     
  if (rectClicked1) {
    fill(lightRect);
  } else {
    fill(rectColor);
  }
  rect(positionX+30, positionY-50, rectSize, rectSize);
  
  
    if (rectClicked2) {
    fill(lightRect);
  } else {
    fill(rectColor);
  }
  rect(positionX-50,positionY,rectSize,rectSize);
  
  
    if (rectClicked3) {
    fill(lightRect);
  } else {
    fill(rectColor);
  }
  rect(positionX+110,positionY,rectSize,rectSize);
  
  
    if (rectClicked4) {
    fill(lightRect);
  } else {
    fill(rectColor);
  }
  rect(positionX+30,positionY+50,rectSize,rectSize);  // rect(positionX+30, positionY-60, rectSize, rectSize);
  
 reciever();
}
  //################################################*****************************UPDATE FUNCTION*******************************###############################//
  

void update(int x, int y) {                                       // check the values of mouseX and mouseY with the following condition 
 
                                                                 //  it take the three defined value to (suppose the cursor is ON the given circle1) 
       if ( cursorOnCircle(positionX, positionY, circleSize) )       //FUNCTION   cursorOnCircle %%%%%%%%%%%%%%%%%%% Please see the cursorOnCircle BELOW
                                                                 
      {                                                         // the condition inside the function is true it entres the loop
                                                                // it assign circleClicked1 TRUE and all other false  @@@@@@@@@@@@@@@@@@please go up to void draw()
    circleClicked1 = true;
    circleClicked2 = rectClicked1 =rectClicked2=rectClicked3=rectClicked4= false;
  } 
   
  else if ( cursorOnCircle(positionX+60, positionY, circleSize) ) 
  {   
   circleClicked2=true;  
    circleClicked1=rectClicked1 =rectClicked2=rectClicked3=rectClicked4= false;
  }
  
  else if ( cursorOnRect(positionX+30, positionY-50) ) {
    rectClicked1 = true;
    circleClicked1=circleClicked2 =rectClicked2=rectClicked3=rectClicked4= false;
  }
 
  else if(cursorOnRect(positionX-50,positionY))
  {
    rectClicked2=true;
     circleClicked1=circleClicked2 = rectClicked1 =rectClicked3=rectClicked4= false;
  }
  
  else if(cursorOnRect(positionX+110,positionY)){
    rectClicked3=true;
    circleClicked1=circleClicked2 = rectClicked1 =rectClicked2=rectClicked4= false;
  }
  
  else if(cursorOnRect(positionX+30,positionY+50)){
    rectClicked4=true;
    circleClicked1=circleClicked2 = rectClicked1 =rectClicked2=rectClicked3= false;   
  }
  
  else {
    circleClicked1=circleClicked2 = rectClicked1 =rectClicked2=rectClicked3=rectClicked4= false;
  }
  
  
}



boolean cursorOnRect(int x, int y)  {
  if (mouseX >= x-(rectSize/2) && mouseX <= x+(rectSize/2) && 
      mouseY >= y-(rectSize/2) && mouseY <= y+(rectSize/2)) {
    return true;
  } else {
    return false;
  }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&************ cursorOnCircle Function  *****************

boolean cursorOnCircle(int x, int y, int dia) {          //  so it check weather the cursor is on the circle or not    
                                                        //(WE ASSUMED cursor is on the circle) so It returns  value #############   true 
                                                        // Please go back to the***************************** UPDATE funtion
  if (sqrt(sq(x-mouseX) + sq(y-mouseY)) < dia/2 ) {
    return true;
  } else {
    return false;
  }
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$***************      MOUSEPRESSED    function*************


void mousePressed()         //  PRE-DEFINED FUNCTION whenever mouse is pressed it comes to here no need to declare it in void draw
{
  if(circleClicked1)          // SO IT WILL PERFORM THE FOLLOWING TASK      
  {
    
   myPort.write(start);
   println("Start");
   
}
   else if(circleClicked2)
  {
  
  myPort.write(stopa);
  println("stop");
    
  }
  else if(rectClicked1){
    myPort.write(forward);
    if(counT==0)counT=2;
if(counT==11&&yFinal<yIntial)counT=2;
if(xFinal>xIntial&&counT==11)counT=3;
if(xFinal<xIntial&&counT==11)counT=4;
if(yFinal>yIntial&&counT==11)counT=5;
 println("forward");
 
  }
   else if(rectClicked2){
    myPort.write(left);
     if(yIntial>yFinal)counT=4;
  if(xFinal>xIntial)counT=2;
  if(xFinal<xIntial)counT=5;
  if(yIntial<yFinal)counT=3;
  if(counT==0)counT=4;
    println("left");

  }
   else if(rectClicked3){
   myPort.write(right);
  if(yIntial>yFinal)counT=3;
 if(xFinal>xIntial)counT=5;
 if(yIntial<yFinal)counT=4;
 if(xFinal<xIntial)counT=2;
 if(counT==0)counT=3;
   println("right");
   
  
  }

  
   else if(rectClicked4){
     myPort.write(backward);
   println("backward");

  }
}
  


void reciever(){
  while(myPort.available()>0)
   {
   int myText= myPort.read();
   
      if(myText=='B'){
      println("You Can Go");
      println("LEFT or RIGHT");
      counT=11;
      }
      if(myText=='R'){
      println("You Can Go");
      println("RIGHT");
        counT=11;
      }
      if(myText=='L'){
      println("You Can Go");
      println("LEFT");
        counT=11;
      }
      if(myText=='P'){
        print(" or FORWARD");
      }
      
   }
}

void drawer(){
  if(counT!=11){
xIntial=x;
yIntial=y;
  }
if(counT==2)y=y-yChange;
if(counT==3)x=x+xChange;
if(counT==4)x=x-xChange;
if(counT==5)y=y+yChange;



if(counT==11){
fill(0,255,0);
ellipse(x,y,20,20);
}




fill(255,0,0);
stroke(255,0,0);
rect(x,y,2,1);
xFinal=x;
yFinal=y;

}
int counT=0;
float x=100,y=600;
float xChange=5,yChange=.3;
float xFinal=0,xIntial=0,yFinal=0,yIntial=0;