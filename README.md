# Monte Carlo Localization

This is for my learning purpose. It's a simple Monte Carlo Localization for a humanoid robot with line points observation that is similar to a mobile soccer robot in MSL League.

The idea is simple, because we don't always see the field lines, why not observe the white points inside the field or boundary of the outer field and then use those points to calculate our position?

![mcl](https://i1234.photobucket.com/albums/ff416/haritsc/Alfarobi/mcl.gif)


# TODO
1. Solve the weighting
2. Why the estimation is wrong?
3. Try AMCL
----

Feel free to ask me, I will be very happy to discuss and learn from others. m.haritsah@mail.ugm.ac.id


### References

1.  Huimin Lu, Xun Li, Hui Zhang, Mei Hu & Zhiqiang Zheng (2013) Robust and real-time self-localization based on omnidirectional vision for soccer robots, Advanced Robotics, 27:10, 799-811, DOI: 10.1080/01691864.2013.785473 

2. Lauer M., Lange S., Riedmiller M. (2006) Calculating the Perfect Match: An Efficient and Accurate Approach for Robot Self-localization. In: Bredenfeld A., Jacoff A., Noda I., Takahashi Y. (eds) RoboCup 2005: Robot Soccer World Cup IX. RoboCup 2005. Lecture Notes in Computer Science, vol 4020. Springer, Berlin, Heidelberg
