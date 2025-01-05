Gate Monitoring System V1.0 
1.2.	Hardware Requirement
1.	RaayanMini
2.	Gate sensor
3.	IR sensor
4.	Audio Module JQ6500
5.	Speaker

1.3.	Main Requirements
The project goals are as follows
1.	Use Reed sensor to identify is the gate is open or not.
2.	Use the IR Beam sensor to identify if the gate is opened from inside or outside.
3.	Play the following audio messages depending on which happens in steps 1 and 2
Gate opened from outside
- Play greeting audio track depending on time as below
1.	Track 5 - between 6:00 am and 11:59 am
2.	Track 6 - between 12:00 pm and 4:59 pm
3.	Track 7 - between 5:00 pm and 7:59 pm
4.	Track 8 - between 8:00 pm and 5:59 am
- Then play audio track 1 (“Welcome to India's only Industrial Embedded Systems training institute Kernel Masters, Please leave footwear and bags on the stands provided. Please Close the Gate”) when gate is opened from outside.
Gate opened from inside
Play audio track 4 (“Thank you for visiting Kernel Masters Please close the Gate”) if gate
is
opened from inside.
4.	After detecting gate has been opened, check periodically if the gate is not closed and play audio track 2 (“Please close the Gate”). Repeat checking gate open/closed condition after the audio track is done playing.
5.	After detecting the gate has been closed, play audio track 3 (“Thank you for closing the Gate”). Then go back to waiting for gate to be opened before starting the above process.

1.4.	Additional Requirements:
•	On power up, GMS should display the below on LCD

	G	A	T	E		M	O	N	I	T	O	R	I	N	G
					V	1	.	0							

•	Display time on LCD on line 1 and date on line 2 when nothing is happening i.e. gate is closed and no audio tracks are being played.

	H	H	:	M	M	:	S	S							
 
	D	D	/	M	M	/	Y	Y							

•	When gate is opened from outside
•	Display “Gate Announce…” on LCD line 1 and “Good Morning!”/“Good Afternoon!”/“Good Evening!”/“Good Night!” depending on greeting message on LCD line 2.

	G	A	T	E		A	N	O	U	N	C	E	.	.	.
	G	o	o	d		M	o	r	n	i	n	g	!		


•	When gate is opened from inside
•	Display “Gate Announce…” on LCD line 1 and “Thank You” on line 2.

	G	A	T	E		A	N	O	U	N	C	E	.	.	.
			T	h	a	n	k		Y	o	u	!			


1.5.	Configuration Requirements
There are two configuration options for this project.
•	Date and Time configuration
o	This is meant to be used during power on and is only to be used to set date and time.
o	After power on and the GMS welcome message is displayed, press the ENTER
switch during the 10 second delay to enter in this configuration mode.
o	After entering this configuration mode, read current date and time from DS1307 RTC and display in below format

	H	H	:	M	M	:	S	S							
	D	D	/	M	M	/	Y	Y							

o	The first modifiable field is hours i.e. this is the default modifiable field. If hours have to be changed, press UP or DOWN switch to change hours. Once the desired value is entered for hours, then press enter to finalize that value and move on to the next modifiable field, minutes.
o	Repeat above step for seconds, date, month and years.
o	Cursor should be displayed for the current modifiable field in order to avoid
confusion.
o	Note that the chance to modify date and time is possible only once. If any incorrect values are entered, power cycle and repeat above steps.
o	Note that ENTER switch can be pressed continuously without making any changes to the values and proceed. In this case, there is no need to update date and time in the DS1307 RTC.
o	Note that if the ENTER switch is not pressed during the 10 second delay after welcome message, proceed forward into gate monitoring functionality.
o	Note that this will be done as one time function call without any tasks being created.
 
•	Volume change
o	During normal gate monitoring functionality, volume for the audio module JQ6500 can be change at any time.
o	This is done by pressing UP or DOWN switch to either increase or decrease volume.
o	Note that you can keep track of the volume range supported on JQ6500 and display the setting on LCD.
o	Note that the volume setting should not be changed beyond the minimum and maximum values supported by the audio module. Once the range is passed, you can use the buzzer to provide audio feedback.
o	Note that this should be implemented in a task, separate from the tasks that implement the functionality.

2.0.	Software architecture - high level
This project should make use of FreeRTOS and should have three tasks. Use flags in software to keep track of various conditions and use protection mechanisms like semaphores etc as required for those flags.

Create the following three tasks and implement the functionality of each tasks as indicated below
Task 1: [Sensor Status]	--	void Task1_SensorStatus(void);
•	Keep waiting for the signal from gate sensor indicating that the gate is open. Once the gate sensor is ON, set Gate_Sensor_Flag.
•	Also keep waiting for the signal from IR sensor. Once the IR sensor is ON, set
IB_Sensor_Flag.

Task 2: [Display Date/Time]	--	void Task2_ReadRTC_WriteLCD_1sec(void);
•	Every 1 second, read date and time from DS1307 RTC and write to the LCD
Task 3: [Gate Announcements]	--	void Task3_Gate_Announcement(void);
•	Whenever Gate_Sensor_Flag is set, then after 50 msec delay, check IR_Sensor_Flag.
o	If IR_Sensor_Flag is set then
	Play audio track 4 as indicated in Main Requirements.
	display messages as indicated in Display Requirements.
o	If IR_Sensor_Flag is not set then
	Play audio track 5/6/7/8 followed by audio track 1 as indicated in Main
Requirements.
	Display messages as indicated in Display Requirements.
o	Create a loop, where track 2 is played every 3 seconds until Gate_Sensor_Flag
is cleared.
o	Finally play audio track 3 and go back to waiting for sensors to change state.
Task 4: [Volume Change]	--	void Task4_Volume_Change(void);
•	Wait on UP or DOWN switch press.
•	Once either switch is pressed, detect which switch is pressed and do the following based on the switched pressed
o	UP switch is pressed
 
	Display current volume on LCD as below, in place is xx.

	H	H	:	M	M	:	S	S							
	D	D	/	M	M	/	Y	Y						x	x

	Increase the volume until the maximum supported by the audio module.
o	DOWN switch is pressed
	Display current volume on LCD as below, in place is xx.
	Deccrease the volume until the minimum supported by the audio module.
o	In case the value entered goes beyond the minimum/maximum volume supported by the audio module, use buzzer to make a sound for 1 second and display the minimum/maximum volume supported.
o	After 1 seconds of no more input from the UP/DOWN switches, send the
command to audio module to modify the volume.
o	Go back to waiting for further input from UP/DOWN switches.
