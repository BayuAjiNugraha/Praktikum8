#include <EEPROM.h>
boolean exitProgram=0;

void setup(){
Serial.begin(9600);
Serial.println("======= EEFROM Accsess Via Serial============");
Serial.println("Type this command to execute EEPROM operation");
Serial.println("Write : for write data to EEPROM");
Serial.println("read  : for read data to EEPROM");
Serial.println("clear : for clear all data in EEPROM");
Serial.println("exit  : for exit from program");
}

void loop (){
int command;
while(!exitProgram){
do {
Serial.print("Type Command>>");
while(Serial.available()==0);
command = readCommandFromSerial();

switch (command){
case 1 : Serial.println("Write EEPROM Selected");
   writeEEPROM();
   break;
case 2 : Serial.println("read EEPROM Selected");
   readEEPROM();
   break;
case 3 : Serial.println("clear EEPROM Selected");
   clearEEPROM();
   Serial.println("clear EEPROM Finished");
   break;
case 4 : Serial.println("Exit From Program");
   exitProgram = 1;
   break;
default: Serial.println("Wrong Command, Please Type Again !");
   break;
}
}
while(command == 0);
}
}
int readCommandFromSerial(){
char stringFromSerial[10];
char data;
int command;
int countData=0;
for(int i=0;i<10;i++){
stringFromSerial[i]=0;
}
while(true){
if(Serial.available()){
data=Serial.read();
Serial.write(data);
if(data=='\n'){
break;
}
else{
if(data!='\r'){
stringFromSerial[countData]=data;
countData++;
}
}
}
}
if(strcmp(stringFromSerial,"write")==0){
command = 1;
}
else if(strcmp(stringFromSerial,"read")==0){
command = 2;
}
else if(strcmp(stringFromSerial,"clear")==0){
command = 3;
}
else if(strcmp(stringFromSerial,"exit")==0){
command = 4;
}
else{
command = 0;
}
return command;

}
int readValFromSerial(){
char stringFromSerial[10];
char data;
int val;
int countData = 0;
for(int i=0;i<10;i++){
stringFromSerial[i]=0;
}
while(true){
if(Serial.available()){
data=Serial.read();
Serial.write(data);
if(data=='\n'){
break;
}
else{
if(data!='\r'){
stringFromSerial[countData]=data;
countData++;
}
}
}
}
sscanf(stringFromSerial,"%d",&val);
return val;
}
void clearEEPROM(){
for(int i=0;i<512;i++){
EEPROM.write(i,0);
}
}
void writeEEPROM(){
int address;
do {
Serial.print("address:");
address=readValFromSerial();
if(address>512){
Serial.println("Addres maximal is 512! Please type again!");
}
}
while(address>512);
int data;
do {
Serial.print("Data :");
data=readValFromSerial();
if(data>512){
Serial.println("Data maximal is 512!, Please type again !");
}
}
while(data>512);
EEPROM.write(address,data);
Serial.println("EEPROM Write Success!");
}
void readEEPROM(){
int address;
do {
Serial.print ("Address :");
address =readValFromSerial();
if(address>512){
Serial.println("Address maximal is 512!, Please type again!");
}
}
while(address>512);
int data = EEPROM.read(address);
Serial.print("Data in Address ");
Serial.print(address,DEC);
Serial.print(":");
Serial.println(data,DEC);
}








