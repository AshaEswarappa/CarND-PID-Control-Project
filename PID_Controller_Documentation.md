In this project, a PID controller is implemneted which enables to drive a vehicle safely in a simulation enviornment.The controller is built for both the speed and throttle values, and parameters are tuned manually.

The PID controller tuning is done manually. Of course this could have been done better using some function for tuning as learnt during the course. Initilaized all the parameters to 0 first and then changed only P parameter to 1. It was observed how the car started steering in proportion to the cross-track error(i.e.. difference between desired and measured value). Then, I started tuning only P-Parameter by reducing a value bit by bit like reducing by 0.1, 0.05 and then fixed to value where car was not doing too much of oscillations.

In the same way, I-Parameter was set to 1 and tried to reduce the value by small portion.However, it was noticed that for this simulator I-Paramater has no influence in controlling the vehicle stability so it was set to 0 itself.

Same procedured applied for D-Paramter, however it was observed the setting a value close to 1 makes the vehicle to drive safely and bit stable.Thus, I didnt tune much here for steering value. But i did trial and error for throttle parameter tuning.

In the similar fashion, throttle value is also calculated and tuned manually such that the value approaches to nearly 0.3. I tried to set the desired speed to different values like 60, 50, 45, and then 40. But it was observed as the speed increases, the vehicle was behaving agressivley like a crazy driver drives on the road. So the desired speed is set to 36.5mph where car is able to drive smoother and safer.

The final tuned parameters for steering can be found in the code line 45. And, for throttle it can be found at 101 line. 

## Effects of PID components:

### - P-Controller: 
Proportion to the cross-track error(CTE) which indicates how far is the car from the middle lane of the road. If the car is far away from the right it steers to the left, if it's slightly to towards left then it steers to the right. The video corresponding to only P-Controller can be found here ![P-Controller](./Ouput/P_Con_0.5.mp4)

### - I-Controller: 
Sum/Integral of all the CTE. In case if there is bias/offset in the CTE, then the integrator acculmulates the error which inturn increases control signal and there by finally reducing error. However, this has very less influnece for the simulator provided. The video corresponding to only I-Controller can be found here ![I-Controller](./Ouput/I_Con_0.5.mp4)

### - D-Controller:
Proportional to the rate of change of CTE/dervative of CTE. The parameter is used to reduce overshooting and dump oscillations caused by the P-parameter. The video corresponding to only D-Controller can be found here ![D-Controller](./Ouput/D_Con_1.0.mp4)