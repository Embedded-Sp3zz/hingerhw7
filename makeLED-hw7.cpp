/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            
*
*
* BLINK FUNCTION
 * 1. Accepts two command line arguments called blink and an integer n
 * 2. The script calls blink USR3 LED n times (a blink is On followed by Off)
 * 3. USR3 LED shall remain on for 1 second and off for 1 second
 * 4. To blink the LED, you should not use flash, trigger, delay_on or delay_off.
 *
 * Example invocation:
 * 	./makeLED-hw7 blink 5
 *
 *
 */


#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc<2){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash or status" << endl;
	cout << " NEW MODE: ./makeLED blink n to blink USR3 led n times" << endl;
	cout << " e.g. makeLED flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }

   //NEW blink function implemented for USR3 LED
   else if (cmd=="blink"){
	  cout << "Blinking the USR3 LED " << argv[2] << " times" << endl; 
	   for(int i = 0; i < atoi(argv[2]); i++){	
		writeLED("/brightness", "1");
		sleep(1);
		writeLED("/brightness", "0");
		sleep(1);
	   }
   }


   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
