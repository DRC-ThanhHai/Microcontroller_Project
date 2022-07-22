# Microcontroller Project

## Intro
- This project is about making a Digital Perpetual Calendar that shows time, day, temperature, and humidity.
- In this project, we used stm32f103C8T6 as the main controller, GLCD for display, RTC ds1307 for time, SHT31 sensor for measuring temperature and humidity, and esp8266 for updating time from the internet.

## Team members
Our team has two members:
- Me (Thanh Hai). I did the software programming part. My responsibilities are to develop software for testing hardware components (push buttons, bell, ...), interface with ds1307, display on GLCD, and write a program for users to interface with the project. (The demo video below shows more about the user interface.)
- My friend (Minh Khoa). He did the hardware and firmware parts. His role is to design PCB and solder components, develop drivers for GLCD and SHT31, interface with the SHT31 sensor using I2C communication, communicate stm32 with esp8266 via UART, and program esp8266 to get time from the NTP server.

## Demo
This is a demo video for our project.
Link: https://youtu.be/uYHr1KI5tts
