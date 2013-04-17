#include <LPC214x.h>
#include <stdio.h>
#include "Serial.h"
#include "Math.h"
#include "lcd.h"
#define resetString "ATZ"
#define Q "Q"
/** 
	1) Setup code / buffers to write out through the UART.
	2) Setup code for LCD interface. g
**/ 

/** Function Prototypes **/
char messageBuffer[8];
char receiveBuffer[8];
char rpmBuffer[50];
char mphBuffer[50];
char throttleBuffer[50];
char loadBuffer[50];
char mpgBuffer[50];

int  saveData = 0;
int rpmOffset;
int mphOffset;
int mpgOffset;
int throttleOffset;
int loadOffset;
int spaceCounter;

int r;

char * welcomeMessage;
char * programMessage;
int resetOK = 0 ;
int convertDecimal(char charVal);
int getFullValue(int intVal);
int * toArray(int number) ;
int CMD = 0;

int programloop;
int rpmCounter;
int throttleCounter;
int loadCounter;
int mphCounter;

void convertNumberIntoArray(unsigned int number);
void testingMPH();
void testingRPM();
void testingThrottle();
void testingLoad();
void newline();
void displaymainMenu();
void engineTiming();
void menuSelect(int choice);
void writeBuffer(char buffer[]);
void purgeBuffer(char buffer[]);
void resetBoard();
void engineLoad();
void engineRPM();
void getSpeed();
void getThrottle();
void init();
void success();
void failure();
//PIDS: 0104
int main() {
	 int x = 0; 
	 init();    // Initialize Board UART 
  init_lcd();
	//displaymainMenu();
	newline();


/** MAIN PROGRAM LOOP **/ 

/** 
ATTN: BO
FOUR PID BUFFERS. 
char rpmBuffer[50];
char mphBuffer[50];
char throttleBuffer[50];
char loadBuffer[50];

**/



while(1){
//testing();

wait:
	lcd_clear();
	lcd_putstring(LINE1,"Test 2");
	x=uart1_getkey();
	
	if(x==0x58){
		 
		 lcd_clear();
		 while(CMD != 0x7E){

		
						lcd_putstring(LINE1,"Logging RPM");
						engineRPM();  
						delay(10000);
						lcd_clear();
						lcd_putstring(LINE2,"Done.");
						
					
					/**Check the status after each send.  We want to make sure that the application is "still there." 
				    If we do not receive a 0x55, then that means the user has exited the screen. Break from loop."
					**/
			    	CMD = uart1_getkey();
			  
			   		if(CMD != 0x55 || CMD == 0x7E){
			            uart1_putc(0x7E);   //echo back termination
									CMD = 0x7E;         //Force exit 
					}
			 }//end while	
}
	else if(x == 0x59){ 

				lcd_clear();
				while(CMD != 0x7E){   

						lcd_putstring(LINE1,"Logging MPH");
						getSpeed();  
						delay(10000);
						lcd_clear();
						lcd_putstring(LINE2,"Done.");
				  	
							CMD = uart1_getkey();
		   		
							if(CMD != 0x55 || CMD == 0x7E){
					            uart1_putc(0x7E);   //echo back termination
								CMD = 0x7E;         //Force exit 
							}

		 	}//end while	
	

	}//end Speed

	else if(x == 0x5A){

				lcd_clear();
				while(CMD != 0x7E){   

						lcd_putstring(LINE1,"Logging load");
						engineLoad();  
						delay(10000);
						lcd_clear();
						lcd_putstring(LINE2,"Done.");
				  	
							CMD = uart1_getkey();
		   		
							if(CMD != 0x55 || CMD == 0x7E){
					            uart1_putc(0x7E);   //echo back termination
								CMD = 0x7E;         //Force exit 
							}

		 	}//end while	
					
	}//end Load
	else if(x == 0x5B){

				lcd_clear();
				while(CMD != 0x7E){   

						lcd_putstring(LINE1,"Logging throttle");
						getThrottle(); 
						delay(10000);
						lcd_clear();
						lcd_putstring(LINE2,"Done.");
				  	
							CMD = uart1_getkey();
		   		
							if(CMD != 0x55 || CMD == 0x7E){
					            uart1_putc(0x7E);   //echo back termination
								CMD = 0x7E;         //Force exit 
							}

		 	}//end while	

	}//end throttle

	else if(x == 0x5C){

				lcd_clear();
				while(CMD != 0x7E){   

						lcd_putstring(LINE1,"Logging Timing");
						engineTiming();
						delay(10000);
						lcd_clear();
						lcd_putstring(LINE2,"Done.");
				  	
							CMD = uart1_getkey();
		   		
							if(CMD != 0x55 || CMD == 0x7E){
					            uart1_putc(0x7E);   //echo back termination
								CMD = 0x7E;         //Force exit 
							}

		 	}//end while	

	}//end timing

	else if(x == 0x5D){

					 	 lcd_clear();  	
						 lcd_putstring(LINE1, "Log IAT");
						 
					 while(CMD != 0x7E){
						 
							


								CMD = uart1_getkey();
					  
					   		if(CMD != 0x55 || CMD == 0x7E){
					            uart1_putc(0x7E);   //echo back termination
								CMD = 0x7E;         //Force exit 
							}

			}//end while

	}//end intake air temp
	
	else if(x == 0x5E){
								 lcd_clear();  	
						 lcd_putstring(LINE1, "Log Voltage");
						 
					 while(CMD != 0x7E){
						    /**Retrieve and send data here **/

									//Must write voltage function. ATS?
									delay(10000);	
								    
									/**Check the status after each send.  We want to make sure that the application is "still there." 
								    If we do not receive a 0x55, then that means the user has exited the screen. Break from loop."
									**/
							    	CMD = uart1_getkey();
							  
							   		if(CMD != 0x55 || CMD == 0x7E){
							            uart1_putc(0x7E);   //echo back termination
										CMD = 0x7E;         //Force exit 
									}


					 	}//end while
	}//end voltage
	
	else if(x == 0x5F){
		
						 lcd_clear();  	
						 lcd_putstring(LINE1, "Log MPG");
						 
					 while(CMD != 0x7E){
								    
								  
										delay(10000);	
					
							    	CMD = uart1_getkey();
							  
							   		if(CMD != 0x55 || CMD == 0x7E){
							        
							            uart1_putc(0x7E);   //echo back termination
										CMD = 0x7E;         //Force exit 
									
									}
						


					 	}//end while
		
		
	}
	
	
	else if(x == 0x35){

	/** RPM (x10) --> MPH (x10) --> Throttle (x10) --> Engine Load (x10) **/
				 newline();
				 newline();
				 menuSelect(x);
				 newline();
				 newline();	
				 			
				 programloop = 0;
				
				 rpmCounter =  0;
				 mphCounter =  0;
				 loadCounter = 0;
				 throttleCounter = 0;
				
				 mphOffset = 0;
				 rpmOffset = 0;
				 throttleOffset = 0;
				 loadOffset = 0;
				 
				 spaceCounter = 0;

				 saveData = 1;	  //1 = save data logging contents into buffers for Sd Card
			

		while(programloop == 0){

				while(rpmCounter < 10){
				
						engineRPM();
						delay(10000);
					//	testingRPM();
						rpmCounter +=1;	
				}//end RPM Sampling	

					newline();
					newline();

				for(r = 0; r < 50;r++){
						uart1_putc(rpmBuffer[r]);
				}					 
			 	newline();
				newline();
				
				delay(10000);
				spaceCounter = 0; 
				while(mphCounter < 10){

				 		getSpeed();
						delay(10000);
						//testingMPH();
						mphCounter +=1;
						
				
				} 
		
				for(r=0;r<26;r++){

				 		uart1_putc(mphBuffer[r]);
					   
				}
				 
				newline();
				newline();


				spaceCounter = 0;
				while(throttleCounter < 10){
				 		//testingThrottle();
						getThrottle();
						delay(10000);
						throttleCounter += 1; 

				}
			
				for(r=0;r<26;r++){

				 		uart1_putc(throttleBuffer[r]);
								}
				 
				newline();
				newline();
				 
						spaceCounter = 0;
				while(loadCounter < 10){
				 		//testingLoad();
						engineLoad();
						delay(10000);
						loadCounter += 1; 

				}
			
				for(r=0;r<26;r++){

				 		uart1_putc(loadBuffer[r]);
								}
				 
						newline();
						newline();
				 
				 
				  programloop = 1;
		}//end while


	} // end Program Loop
	
	else
		goto wait;
		 
	
		  }//end while 1
}//end main




void writeBuffer(char buffer[]){

	uart0_puts(buffer);

}



void init(){
	 //Set up 9600 Baud / 8N1 Protocol 
 	 uart1_init();
 	 uart0_init();
}































	 /** Changelog 


			- Engine load and Engine throttle, changed the CMD byte 
			- Add loop to engine throttle/engine load
			- fix option 5


	 **/

























/** OBD-II FUNCTIONS : WILL WORK ON MOVING THESE TO A SEPARACE C FILE. **/
					
void resetBoard(){

		  int x = 0;
		  int i;
		  messageBuffer[0] = 'A';
		  messageBuffer[1] = 'T';
		  messageBuffer[2] = 'Z';
		  messageBuffer[3] = '\r';   //carriage return
		  messageBuffer[4] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
    	  delay(10000);

     	
		 success();
}





void getMPG(){
	

	int vss = 0; 
	int maf = 0;
    int total = 0;
    int * convertedArray;
int i;
	vss = mpgSpeed();
	maf = engineMAF();

	total = 71.07 * vss / maf;

	/** Need to log to SD card **/

	/**Convert to individual int array to save**/
	convertedArray = toArray(total);

	/**Convert each int back to char to save into SD card **/
for(i=2;i>=0;i--){
					   if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
					  else{
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if			
								   
						}//end else		    
						    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
										mpgBuffer[mpgOffset] = convertedArray[i];
										mpgOffset = mpgOffset + 1;
										mpgBuffer[mpgOffset] = 0x20;	
										mpgOffset = mpgOffset + 1;
										
									}
								   else{
									mpgBuffer[mpgOffset] = convertedArray[i];
									mpgOffset = mpgOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
									else{
									 	
									 	uart1_putc(convertedArray[i]); //output the mpg to the bluetooth

									}//not saving data					
						    } //end if
					}//end for loop
}

int mpgSpeed(){

/** This function is different from getSpeed() in that we only return the full integer value to the MPG function**/

char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
	

		/** Format:  41 0D XX **/ 
		/** Result given in km/h, need to convert **/
		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = 'D';   
		  messageBuffer[4] = '\r';
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);  


	while(repeat==1){
				 	   
					response1 = uart0_getkey();
				
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'D'
				
										 	if(cmd2 == 0x44){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

												intArray[0] = data2;
												intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 0.60;     		//Convert to MPH.  approximate.  
			
					convertedArray = toArray(decimalFull);

							
						//Return the speed to the MPG function
						return decimalFull;




											}//end 'D'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while
}//end mpg Engine Speed

int engineMAF(){
//Returns the value of the MAF for the MPG function
	  	  char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;
		  int data3;
		  int data4;
		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
		  int RPM_counter = 0;

		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '1';
		  messageBuffer[3] = '0';   
		  messageBuffer[4] = '\r';
		  messageBuffer[5] = '\0';   //Null Terminator
		
			 repeat = 1;
			
			 uart0_puts(messageBuffer); 

				while(repeat==1){
				 	   
					response1 = uart0_getkey();
	
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
								if(response2 == 0x31){	  		//check for '1'
										
									    space = uart0_getkey(); //read in '0x20'
										cmd1 = uart0_getkey();   //read in '1'
						
								
									 if(cmd1 == 0x31){			
									
										 cmd2 = uart0_getkey();  //read in '0'
									
										 	if(cmd2 == 0x30){	 //gather data
													
												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												
					
												space = uart0_getkey();
												data3 = uart0_getkey();
												data4 = uart0_getkey();

												intArray[0] = data4;
												intArray[1] = data3;
												intArray[2] = data2;
												intArray[3] = data1;
												
					for(i=0;i<4;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
						
					fullValue[3] = 4096 * intArray[3];
					fullValue[2] = 256 * intArray[2];
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1] + fullValue[2] + fullValue[3];
				
					decimalFull = decimalFull / 100;  //get MAF value 

					convertedArray = toArray(decimalFull);	
				
					
							//For the MAF, we don't need to convert since we're not outputting the RAW MAF reading
						    //We want to just send an integer value back to the MPG function for it to calculate 
							return decimalFull;
							//uart1_putc(convertedArray[i]);


								//Prints out each char of the number individually. 
								//For MAF, we dont send back, we want to return the int value to the MPG function.  

							} // end '0' search 
						}//end '1' search
				}//end '1' search 
		}// end '4' search
	
	}//end while Retrieve 	
						
}//end engineMAF

void intakeAirTemp(){

		  char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = 'F';  
		  messageBuffer[4] = '\r'; 
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);  


	while(repeat==1){
				 	   
					response1 = uart0_getkey();
						 //uart0_putc(response1);
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'F'
				
										 	if(cmd2 == 0x46){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

												intArray[0] = data2;
												intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = (decimalFull) - 40;  		//Intake Air Temperature formula
			
					convertedArray = toArray(decimalFull);


					uart1_putc(convertedArray[i]); //output timing advance to bluetooth
								
			
											
											repeat = 0;
											}//end 'E'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while


}//end intake air temperature

void engineTiming(){

		  char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = 'E';  
		  messageBuffer[4] = '\r'; 
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);  


	while(repeat==1){
				 	   
					response1 = uart0_getkey();
						 //uart0_putc(response1);
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'E'
				
										 	if(cmd2 == 0x45){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

												intArray[0] = data2;
												intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = (decimalFull / 2) - 64;  		//Timing advance formula
			
					convertedArray = toArray(decimalFull);


					uart1_putc(convertedArray[i]); //output timing advance to bluetooth
								
			
											
											repeat = 0;
											}//end 'E'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while


}//end timing advance
void engineLoad(){

		  char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = '4';  
		  messageBuffer[4] = '\r'; 
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);  


	while(repeat==1){
				 	   
					response1 = uart0_getkey();
						 //uart1_putc(response1);
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'D'
				
										 	if(cmd2 == 0x34){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

												intArray[0] = data2;
												intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 0.60;     		//Convert to MPH.  approximate.  
			
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
						   	 if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
					  else{
		
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if
																
							}//end else					
									//	uart1_putc(convertedArray[i]);
								    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
										loadBuffer[loadOffset] = convertedArray[i];			 
										loadOffset = loadOffset + 1;
										loadBuffer[loadOffset] = 0x20;	
										loadOffset = loadOffset + 1;
									}
								   else{
									loadBuffer[loadOffset] = 	convertedArray[i];
									loadOffset = loadOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData

							else{
								   		
										uart1_putc(convertedArray[i]);


							}
												
													
				} //end if
			}//end for loop
												  if(saveData==0){
													/**Print MPH Tag **/
													uart1_putc(0x20); //Space
													uart1_putc(0x25); //'%'
													uart1_putc(0x0D);//CR

													}
														 	repeat = 0;
											}//end 'D'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while


}


void engineRPM(){

	  	  char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;
		  int data3;
		  int data4;
		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
		  int RPM_counter = 0;

		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = 'C';   
		  messageBuffer[4] = '\r';
		  messageBuffer[5] = '\0';   //Null Terminator
		
			 repeat = 1;
			
			 uart0_puts(messageBuffer); 

				while(repeat==1){
				 	   
					response1 = uart0_getkey();
	
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
								if(response2 == 0x31){	  		//check for '1'
										
									    space = uart0_getkey(); //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
						
								
									 if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'C'
									
										 	if(cmd2 == 0x43){	 //gather data
													
												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												
					
												space = uart0_getkey();
												data3 = uart0_getkey();
												data4 = uart0_getkey();

												intArray[0] = data4;
												intArray[1] = data3;
												intArray[2] = data2;
												intArray[3] = data1;
												
					for(i=0;i<4;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
						
					fullValue[3] = 4096 * intArray[3];
					fullValue[2] = 256 * intArray[2];
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1] + fullValue[2] + fullValue[3];
				
					decimalFull = decimalFull / 4;  //get true RPM value

					convertedArray = toArray(decimalFull);	
				
					for(i=3;i>=0;i--){
				
					if(convertedArray[i] <= 0x09 || convertedArray[i] >= 0x00 ){
						convertedArray[i] = convertedArray[i] + 0x30;
						
					if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
												
						convertedArray[i] = 0x30;
					}//end if

						    /**Save data into buffers for SD Card **/
					if(saveData == 1){
								 		
									if(spaceCounter == 3){

									 	spaceCounter = 0;
										rpmBuffer[rpmOffset] = convertedArray[i];
										rpmOffset = rpmOffset + 1;
										rpmBuffer[rpmOffset] = 0x20;	
										rpmOffset = rpmOffset + 1;
										repeat = 0;
									}
								   else{
									rpmBuffer[rpmOffset] = 	convertedArray[i];
									rpmOffset = rpmOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
						
							else{

							 	uart1_putc(convertedArray[i]);
							}


						}//end if
				
				}//end for loop

			if(saveData==0){
			
				uart1_putc(0x20);	 //Space
				//uart1_putc(0x52);    //R
				//uart1_putc(0x50);	 //P
				//uart1_putc(0x4D);	 //M
				//uart1_putc(0x0D);  	//Carriage Return
				 }
				repeat=0;
					   

							} // end 'C' search 
						}//end '0' search
				}//end '1' search 
		}// end '4' search
	
	}//end while Retrieve 	
						
}//end RPM
					

						

						 


void getSpeed(){

char decimalArray[8];
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;
	

		/** Format:  41 0D XX **/ 
		/** Result given in km/h, need to convert **/
		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '0';
		  messageBuffer[3] = 'D';   
		  messageBuffer[4] = '\r';
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);  


	while(repeat==1){
				 	   
					response1 = uart0_getkey();
				
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x30){
									
										 cmd2 = uart0_getkey();  //read in 'D'
				
										 	if(cmd2 == 0x44){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

												intArray[0] = data2;
												intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 0.60;     		//Convert to MPH.  approximate.  
			
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
				
				 if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
					  else{	
		
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if
																
							}//end else
							
											
							//uart1_putc(convertedArray[i]);

								    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
										mphBuffer[mphOffset] = convertedArray[i];
										mphOffset = mphOffset + 1;
										mphBuffer[mphOffset] = 0x20;	
										mphOffset = mphOffset + 1;
										repeat = 0;
									}
								   else{
									mphBuffer[mphOffset] = 	convertedArray[i];
									mphOffset = mphOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
							else{
							 	uart1_putc(convertedArray[i]);
							
							}					
													
											
											
											
								} //end if

				
				}//end for loop
												  if(saveData == 0){
													/**Print MPH Tag **/
													uart1_putc(0x20); //Space
													uart1_putc(0x4D); //'M'
													uart1_putc(0x50); //'P'
													uart1_putc(0x48); //'H'
													uart1_putc(0x0D); //CR
													}
													repeat = 0;

											}//end 'D'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while
}//end Engine Speed

void getThrottle(){
	
		  int response1;
		  int response2;
		  int repeat = 1;
		  int space;
		  int cmd1;
		  int cmd2; 
		  int data1;
		  int data2;

		  int i;
		  int value[8];
		  int fullValue[8];
		  int intArray[8];
		  int decimalFull;
		  int * convertedArray;
		  int data = 0;

		  messageBuffer[0] = '0';
		  messageBuffer[1] = '1';
		  messageBuffer[2] = '1';
		  messageBuffer[3] = '1';   
		  messageBuffer[4] = '\r';
		  messageBuffer[5] = '\0';   //Null Terminator

		  uart0_puts(messageBuffer);
		  delay(100);


		  	while(repeat==1){
				 	   
					response1 = uart0_getkey();
					
						if(response1 == 0x34){   //check for '4'
											
						  	response2 = uart0_getkey();
			
							
								if(response2 == 0x31){	  		 //check for '1'
										
									    space = uart0_getkey();  //read in '0x20'
										cmd1 = uart0_getkey();   //read in '0'
								
									if(cmd1 == 0x31){
									
										 cmd2 = uart0_getkey();  //read in 'D'
				
										 	if(cmd2 == 0x31){	 //gather data

												space = uart0_getkey();
												data1 = uart0_getkey();
												data2 = uart0_getkey();
												/** data1 is the most significant bit **/ 

						intArray[0] = data2;
						intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 100;     		//Convert to MPH.  approximate.  
				    decimalFull = decimalFull/255;
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
					   if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
					  else{
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if			
								   
						}//end else		    
								    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
										throttleBuffer[throttleOffset] = convertedArray[i];
										throttleOffset = throttleOffset + 1;
										throttleBuffer[throttleOffset] = 0x20;	
										throttleOffset = throttleOffset + 1;
										repeat = 0;
									}
								   else{
									throttleBuffer[throttleOffset] = convertedArray[i];
									throttleOffset = throttleOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
									else{
									 	uart1_putc(convertedArray[i]);

									}//not saving data					
						    } //end if
					}//end for loop
													if(saveData == 0){
													/**Print MPH Tag **/
													uart1_putc(0x20); //Space
													uart1_putc(0x25); //'%'
													uart1_putc(0x0D); //CR
													}
													repeat = 0;

											}//end 'D'
										}//end '0'
									}//end '1'
								}//end '4'
							}//end while
}//end getThrottle



int convertDecimal(char charVal){

	 int decimalValue;

	  	if(charVal >= 0x30 && charVal<=0x39) { //Char is 0-9 

				decimalValue = charVal - 0x30; //remainder will be the decimal value. 

				return decimalValue;  //change this. 					   
		}//end 0-9
		
		else if(charVal>=0x41 && charVal<=0x46){   //Char is A-F

				decimalValue = 	charVal - 0x31; 
				decimalValue = decimalValue - 6; //Adjust value
				return decimalValue;
		}
		else{
		 		return 0;

		}
}// end convertDecimal


void success(){

 	  messageBuffer[0] = 'D';
	  messageBuffer[1] = 'O';
	  messageBuffer[2] = 'N';
	  messageBuffer[3] = 'E';
	  messageBuffer[4] = '\r';   //line feed
	  messageBuffer[5] = '\0';   //Null Terminator
	  
	  uart1_puts(messageBuffer);
}


void failure(){

      messageBuffer[0] = 'N';
	  messageBuffer[1] = 'O';
	  messageBuffer[2] = '!';
	  messageBuffer[3] = '\r';   //line feed
	  messageBuffer[4] = '\0';   //Null Terminator
	  
	  uart1_puts(messageBuffer);
}

void purgeBuffer(char buffer[]){

 memset(buffer,0,sizeof(buffer));


}


int * toArray(int number)
{
    int n = log10(number) + 1;
    int i;
    int numberArray[8];
    for ( i = 0; i < n; ++i, number /= 10 )
    {
        numberArray[i] = number % 10;
    }
    return numberArray;
}


void testingMPH(){
		  /** Format:  data1--data2--data3--data4 **/
				/** Tests Passed: 
						-RPM
						-MPH
				**/
						
		
	int data1 = 0x31;
	int data2 = 0x46;
	int data3 = 0x31;
	int data4 = 0x39;
	int intArray[8];
	int fullValue[8];
	int * convertedArray;
	int decimalFull;
	int i;
		
						intArray[0] = data2;
						intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 0.60;     		//Convert to MPH.  approximate.  
			
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
				
						 if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
				else{
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if
												//	uart1_putc(convertedArray[i]);
														
														    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
									
										mphBuffer[mphOffset] = convertedArray[i];
											 
										mphOffset = mphOffset + 1;
										mphBuffer[mphOffset] = 0x20;
											
										mphOffset = mphOffset + 1;
									}
								   else{
									mphBuffer[mphOffset] = 	convertedArray[i];
									mphOffset = mphOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
														
													
												} //end if

												}//end else
				
										}//end for loop

													/**Print MPH Tag 
													uart1_putc(0x20); //Space
													uart1_putc(0x4D); //'M'
													uart1_putc(0x50); //'P'
													uart1_putc(0x48); //'H'
													uart1_putc(0x0D); //CR
																				  **/
}

void testingRPM(){
	   		
	int data1 = 0x30;
	int data2 = 0x46;
	int data3 = 0x31;
	int data4 = 0x39;
	int intArray[8];
	int fullValue[8];
	int * convertedArray;
	int decimalFull;
	int i;

 												intArray[0] = data4;
												intArray[1] = data3;
												intArray[2] = data2;
												intArray[3] = data1;
												
					for(i=0;i<4;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
						
					fullValue[3] = 4096 * intArray[3];
					fullValue[2] = 256 * intArray[2];
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1] + fullValue[2] + fullValue[3];
				
					decimalFull = decimalFull / 4;  //get true RPM value

					convertedArray = toArray(decimalFull);	
				
					for(i=3;i>=0;i--){
						   	
							
					if(convertedArray[i] <= 0x09 || convertedArray[i] >= 0x00 ){
						convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													//Trash, set to 0? 
													convertedArray[i] = 0x30;
										}//end if
					    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 3){

									 	spaceCounter = 0;
									
										rpmBuffer[rpmOffset] = convertedArray[i];
											 
										rpmOffset = rpmOffset + 1;
										rpmBuffer[rpmOffset] = 0x20;
											
										rpmOffset = rpmOffset + 1;
									}
								   else{
									rpmBuffer[rpmOffset] = 	convertedArray[i];
									rpmOffset = rpmOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
						
						}//end if
			
				}//end for loop
}



void testingThrottle(){

	int data1 = 0x31;
	int data2 = 0x46;
	int data3 = 0x31;
	int data4 = 0x39;
	int intArray[8];
	int fullValue[8];
	int * convertedArray;
	int decimalFull;
	int i;
		
						intArray[0] = data2;
						intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 100;     		//Convert to throttle.  
					decimalFull = decimalFull / 255;
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
				
						 if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
				else{
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if
													//uart1_putc(convertedArray[i]);
														
														    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
									
										throttleBuffer[throttleOffset] = convertedArray[i];
											 
										throttleOffset = throttleOffset + 1;
										throttleBuffer[throttleOffset] = 0x20;
											
										throttleOffset = throttleOffset + 1;
									}
								   else{
									throttleBuffer[throttleOffset] = convertedArray[i];
									throttleOffset = throttleOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
														
													
												} //end if

												}//end else
				
										}//end for loop
												/**Print MPH Tag **/
													uart1_putc(0x20); //Space
													uart1_putc(0x25); //'%'
													uart1_putc(0x0D); //CR
													//repeat = 0;

}


 void testingLoad(){

		int data1 = 0x31;
	int data2 = 0x46;
	int data3 = 0x31;
	int data4 = 0x39;
	int intArray[8];
	int fullValue[8];
	int * convertedArray;
	int decimalFull;
	int i;
		
						intArray[0] = data2;
						intArray[1] = data1;
						
												
					for(i=0;i<2;i++){	
						intArray[i] = convertDecimal(intArray[i]);
					 }
				
					fullValue[1] = 16 * intArray[1];
					fullValue[0] = 1 * intArray[0];		
						
					decimalFull = fullValue[0] + fullValue[1];
					decimalFull = decimalFull * 100;     		//Convert to throttle.  
					decimalFull = decimalFull / 255;
					convertedArray = toArray(decimalFull);

				for(i=2;i>=0;i--){
				
						 if(i==2){	 //check msb for 0, if 0; do not display


						  		if(convertedArray[2] == 0){

								 	convertedArray[2] = 0x00;
								}

						 }
				else{
					if(convertedArray[i] <= 9 || convertedArray[i] >= 0 ){
					
							convertedArray[i] = convertedArray[i] + 0x30;
						
								if(convertedArray[i] > 0x39 || convertedArray[i] < 0x30){  //Not between 0-9
													
													convertedArray[i] = 0x30;
										}//end if
													//uart1_putc(convertedArray[i]);
														
														    /**Save data into buffers for SD Card **/
							if(saveData == 1){
									
									if(spaceCounter == 1){

									 	spaceCounter = 0;
									
										loadBuffer[loadOffset] = convertedArray[i];
											 
										loadOffset = loadOffset + 1;
										loadBuffer[loadOffset] = 0x20;
											
										loadOffset = loadOffset + 1;
									}
								   else{
									loadBuffer[loadOffset] = convertedArray[i];
									loadOffset = loadOffset + 1; 
									spaceCounter += 1;
									}//end else
							}//end saveData
														
													
												} //end if

												}//end else
				
										}//end for loop
												/**Print MPH Tag **/
													uart1_putc(0x20); //Space
													uart1_putc(0x25); //'%'
													uart1_putc(0x0D); //CR
													//repeat = 0;
 

	  

}//end test load




void newline(){
 	uart1_putc(0x0D);
	uart1_putc(0x0A);


}

void displaymainMenu(){
welcomeMessage = "Induzione Logging Tool v1.0";
uart1_puts(welcomeMessage);
newline();
newline();

programMessage = "Please select one of the following.";
uart1_puts(programMessage);
newline();
newline();

programMessage = "R-reset";
uart1_puts(programMessage);
newline();

programMessage = "1- Read Vehicle RPM ";
uart1_puts(programMessage);
newline();

programMessage = "2- Read Vehicle Speed (MPH)";
uart1_puts(programMessage);
newline();

programMessage = "3- Throttle Position";
uart1_puts(programMessage);
newline();

programMessage = "4- Engine Load";
uart1_puts(programMessage);
newline();

programMessage = "5-Save Snapshot to SD Card";
uart1_puts(programMessage);
newline();

}

void menuSelect(int choice){

			if(choice == 0x31){
				
			 	programMessage = "Selected #1.  Reading Vehicle's RPM ";
				uart1_puts(programMessage);
				newline();
				newline();

			}
			else if(choice == 0x32){

			 	programMessage = "Selected #2. Reading Vehicle's Speed";
				uart1_puts(programMessage);
				newline();
				newline();
			}
			else if(choice == 0x72){
				programMessage = "System Reset:";
				uart1_puts(programMessage);
				uart1_putc(0x20);
			}
			else if(choice == 0x35){
			 	programMessage = "Logging...Saving Data to SD Card";
				uart1_puts(programMessage);
				newline();
				newline();
			}
			else if(choice == 0x33){

				programMessage = "Selected #3. Reading Throttle Position.";
				uart1_puts(programMessage);
				newline();
				newline();

			}
			else if(choice == 0x34){
				programMessage = "Selected #4. Reading Engine Load.";
				uart1_puts(programMessage);
				newline();
				newline();
			 	

			}


}

