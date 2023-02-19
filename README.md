# Click Player
Simple C++ click player that plays back click delays

## Download
[Download](https://github.com/buxh/Click-Player/releases/download/v2/Click_Recorder_and_Player.zip)

## How to implement your clicks
Put click delays in [clicks::clickdata](https://github.com/buxh/Click-Player/blob/main/clicker/clicks/clicks.cpp#L4).

```c++
std::vector<int> clicks::clickdata = { 98,43,57,110,43,60,44,69,44,58 };
```

In the [releases](https://github.com/buxh/Click-Player/releases) tab a click recorder has been provided along with a compiled version of the click player. To start recording clicks just open `Recorder.exe` and start clicking in game. After you are happy with the clicks go to this [website](https://delim.co/) and paste the click data from the txt into the "Column Data Here" tab then click the blue and white ">" button. Copy the contents of the "Delimited Data Here" tab and paste it into clicks.cpp inside clicks::clickdata. This site allows you to separate each value so you can add it to the vector.

## Preview
<img src="https://i.imgur.com/4lCv6IS.png"/>

## Features
 - Plays back click delays in milliseconds
 - Random start point
 - View CPS
 - Click data information
 - Command line arguments

## To do
 - [x] Upscale / CPS Boost, adding or reducing milliseconds
 - [x] Click in inventory
 - [x] Right mouse button lock
 - [ ] ImGui
 - [ ] Self Destruct
 - [ ] Auto pot
 - [ ] Break blocks
 - [ ] Jitter
 - [ ] Click Profiles
 - [ ] Config Creation
 - [ ] Slot Whitelist
 - [ ] Option to grab delays from txt file

 If you want anything added [create an issue](https://github.com/buxh/Click-Player/issues) and suggest it or message me on discord: `envy#4339`

## Support
All my socials are found [here](https://solo.to/buxh) contact me for help.
