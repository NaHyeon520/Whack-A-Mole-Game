# Whack-A-Mole Game

Microcontroller: Arduino Mega 2560 <br>
Main Components: LED, DC Motor, Infrared Obstacle Avoidance Sensor, Text LCD, Buzzer

<ul>
           <li>LED: Mole. If the light is on, it means that the mole has come out.</li>
           <li>DC Motor: When the user loses all of their life count, it will roll the wheel and run away from the user.</li>
           <li>Infrared Obstacle Avoidance Sensor: This recognizes whether the user has hit the mole or not. The user should hit this sensor while the LED is on.</li>
           <li>Text LCD: It informs the user of the start of the game, left life counts, end message, and total score.</li>
           <li>Buzzer: It makes different sounds when the user hits the mole or not. When the game ends, it plays the music. </li>
</ul>


![hello](https://github.com/NaHyeon520/Whack-A-Mole-Game/assets/62274608/5c52041c-421c-4d81-a492-74f4e8c981e8)

When the user turns on the game, "Hello" appears on the text LCD.

![game](https://github.com/NaHyeon520/Whack-A-Mole-Game/assets/62274608/73084ffb-4286-4f62-bb3e-719ab7da836b)

The game starts when the user pushes the start button on the breadboard. Text LCD will show the left life count.

![mole](https://github.com/NaHyeon520/Whack-A-Mole-Game/assets/62274608/54d3ce5e-4b67-4c05-83c8-541add8252ff)

When the LED is on, it means the mole has come out. Eight LEDs in the middle of the board are moles, and the surrounding sensor is the Infrared Obstacle Avoidance Sensor. The user should touch this sensor to hit the mole in time. 

![end](https://github.com/NaHyeon520/Whack-A-Mole-Game/assets/62274608/90ec70c6-9b9b-4a70-a396-325310df5ea9)

If the user loses all of their life count, the game ends. Buzzer plays the music and the DC Motor works, running away from the user:) 
Good Luck!
