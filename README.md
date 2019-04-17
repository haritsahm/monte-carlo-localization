# Augmented Monte Carlo Localization

This is an Augmented Monte Carlo Localization for a humanoid robot with line points observation that is similar to a mobile soccer robot in MSL League.

The idea is because we don't see the field lines all the time, why don't we observe the white points from a line or boundary of the outer field and then use those points to calculate our position?

### Self Localize
![self-localize](https://oi1234.photobucket.com/albums/ff416/haritsc/Alfarobi/self-localize.gif)

### Kidnapping Problem
![kidnapping problem](https://oi1234.photobucket.com/albums/ff416/haritsc/Alfarobi/kidnapped.gif)

### Simple line scanning to find field points
See the robot's fov area in white

![fov][robot-fov]
![line scan][line-scan]

[line-scan]: https://oi1234.photobucket.com/albums/ff416/haritsc/Alfarobi/line_scanning.png

[robot-fov]: https://oi1234.photobucket.com/albums/ff416/haritsc/Alfarobi/fov_robot.png

Feel free to ask me, I will be very happy to discuss and learn from others. m.haritsah@mail.ugm.ac.id

### Control

| Key | Action |
| -------- | -------- |
| W     | +5 in Robot's Y     |
| S     | -5 in Robot's Y     |
| A     | -5 in Robot's X     |
| D     | +5 in Robot's X     |
| E     | +2 in Robot's Heading     |
| Q     | -2 in Robot's Heading     |

### Requirements
- [x] OpenCV 3
- [x] Qt 5.9
- [x] YAML

### Todo List

- [x] MCL
- [x] AMCL
- [x] Line Points Observation
- [ ] Field Lines Observation
- [x] Number of particles adaptation



### References

> 1.  Huimin Lu, Xun Li, Hui Zhang, Mei Hu & Zhiqiang Zheng (2013) Robust and real-time self-localization based on omnidirectional vision for soccer robots, Advanced Robotics, 27:10, 799-811, DOI: 10.1080/01691864.2013.785473 

> 2. Lauer M., Lange S., Riedmiller M. (2006) Calculating the Perfect Match: An Efficient and Accurate Approach for Robot Self-localization. In: Bredenfeld A., Jacoff A., Noda I., Takahashi Y. (eds) RoboCup 2005: Robot Soccer World Cup IX. RoboCup 2005. Lecture Notes in Computer Science, vol 4020. Springer, Berlin, Heidelberg

> 3. Sebastian Thrun, Wolfram Burgard, and Dieter Fox. 2005. Probabilistic Robotics (Intelligent Robotics and Autonomous Agents). The MIT Press. 

> 4. Aguiar, L., Máximo, M. and Pinto, S. (n.d.). Monte Carlo Localization for Robocup 3D Soccer Simulation League.

> 5. Messias, J., Santos, J., Estilita, J. and Lima, P. (2008). Monte Carlo Localization Based on Gyrodometry and Line-Detection. In: 8th Conference on Autonomous Robot Systems and Competitions.
