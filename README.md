# Augmented Monte Carlo Localization

![gui][GUI]

This is an Augmented Monte Carlo Localization for a humanoid robot with line points observation that is similar to a mobile soccer robot in MSL League.

The idea is because we don't see the field lines all the time, why don't we observe the white points from a line or boundary of the outer field and then use those points to calculate our position?

### Self Localize
|Field Points | Field Lines | 
|---|---|
|![field-point][field_point] | ![field-lines][field_lines] |

![self-loc][self_loc]

### Kidnapping Problem
![kidnapping problem][kidnap]

### Simple line scanning to find field points
See the robot's fov area in white. This is a very simple using line iterator

|Field Points | Field Lines | 
|---|---|
|![fov][robot-fov] | ![line scan][line-scan] |

### Youtube Video
[![Youtube-video](https://img.youtube.com/vi/j8OzGcBkZvM/0.jpg)](https://www.youtube.com/watch?v=j8OzGcBkZvM)

### Control

| Key | Action |
| -------- | -------- |
| W     | +5 in Robot's Y     |
| S     | -5 in Robot's Y     |
| A     | -5 in Robot's X     |
| D     | +5 in Robot's X     |
| E     | +2 in Robot's Heading     |
| Q     | -2 in Robot's Heading     |
| Use Heading | Sse robot's heading for weighting |
| Adaptive Particle | Use the adaptive particle algorithm |
| Debug Features | To view lines from robot fov |

### Requirements

    1. OpenCV 3
    2. Qt 5.9
    3. YAML
    4. C++11

### Todo List

- [x] MCL
- [x] AMCL
- [x] Line Points Observation
- [x] Field Lines Observation
- [x] Number of particles adaptation


Feel free to ask me, I will be very happy to discuss and learn from others. m.haritsah@mail.ugm.ac.id



### References

> 1.  Huimin Lu, Xun Li, Hui Zhang, Mei Hu & Zhiqiang Zheng (2013) Robust and real-time self-localization based on omnidirectional vision for soccer robots, Advanced Robotics, 27:10, 799-811, DOI: 10.1080/01691864.2013.785473 

> 2. Lauer M., Lange S., Riedmiller M. (2006) Calculating the Perfect Match: An Efficient and Accurate Approach for Robot Self-localization. In: Bredenfeld A., Jacoff A., Noda I., Takahashi Y. (eds) RoboCup 2005: Robot Soccer World Cup IX. RoboCup 2005. Lecture Notes in Computer Science, vol 4020. Springer, Berlin, Heidelberg

> 3. Sebastian Thrun, Wolfram Burgard, and Dieter Fox. 2005. Probabilistic Robotics (Intelligent Robotics and Autonomous Agents). The MIT Press. 

> 4. Aguiar, L., Máximo, M. and Pinto, S. (n.d.). Monte Carlo Localization for Robocup 3D Soccer Simulation League.

> 5. Messias, J., Santos, J., Estilita, J. and Lima, P. (2008). Monte Carlo Localization Based on Gyrodometry and Line-Detection. In: 8th Conference on Autonomous Robot Systems and Competitions.


[line-scan]: https://i.imgur.com/yrhnKGx.png

[robot-fov]: https://i.imgur.com/HwwXcNs.png

[field_point]: https://i.imgur.com/zouLCot.png

[field_lines]: https://i.imgur.com/ZDvvFti.png

[self_loc]: https://i.imgur.com/ISZDJvz.gif

[kidnap]: https://i.imgur.com/z9HkNtG.gif

[GUI]: https://i.imgur.com/K0J2ON5.png
