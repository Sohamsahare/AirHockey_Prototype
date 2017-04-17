
//
//  main.cpp
//  shooting
//
//  Created by Harsh Jain on 4/15/17.
//  Copyright © 2017 Crispy Games Private Limited. All rights reserved.
//
//The following code solves cases 1, 2 and 3. Code is written by Soham Sahare and Amrut Kumar.
//All the cases were tested on clone project made on unity3D.
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#define PUCK_RADIUS 40
#define MALLET_RADIUS 80
#define WALL_WIDTH 768
#define WALL_HEIGHT 1024
#define GOAL_WIDTH 300
#define MALLET_MAX_SPEED 200
#define PI 3.14159265
#define CENTER_LINE 384
#define PLAYABLE_HALF_Y 512

struct Point {
    float x;
    float y;
};

using namespace std;
typedef Point Velocity;

float speed(Velocity v) {
    return v.x * v.x + v.y * v.y;
}
double getDistance(Point X,Point Y){
    return sqrt((X.x-Y.x)*(X.x-Y.x) + (X.y-Y.y)*(X.y-Y.y));
}

Velocity intercept(const Point &mallet, const Point &puck, const Velocity* ps) {
    Velocity ret;
    //Case 1: Static Puck (Start Of Game)
    if(ps->x == 0 && ps->y == 0){
        Point hit_direction;
        hit_direction.x = puck.x - mallet.x ;
        hit_direction.y = puck.y - mallet.y;
        float mag_hit_direction = sqrt(hit_direction.x*hit_direction.x + hit_direction.y*hit_direction.y);
        //To normalize the vector hit_direction
        //cout << hit_direction.x << " " << hit_direction.y << "\n" ;
        hit_direction.x = hit_direction.x / mag_hit_direction;
        hit_direction.y = hit_direction.y / mag_hit_direction;
        //cout << hit_direction.x << " " << hit_direction.y << "\n" ;
        if(hit_direction.x == 0 ){
            ret.x = 0;
            ret.y = hit_direction.y * MALLET_MAX_SPEED ;
        }
        else{
            ret.x = hit_direction.x * MALLET_MAX_SPEED / sqrt(2);
            ret.y = hit_direction.y * MALLET_MAX_SPEED / sqrt(2);
        }
    }
    //Case 2: Head On Collision .
    else if(ps->x == 0){
        if(mallet.x == puck.x){
            if(ps->y < 500){
                ret.x = ps->x;
                ret.y = MALLET_MAX_SPEED;
            }
            else{
                ret.x = 0;
                ret.y = 0;
            }
        }
        //If this 'if' statement is not satisfied then the case that we are dealing with is a case of Oblique Collision which will be dealt in Case 3.
    }
    //Case 3: Oblique Collisions. (Bouncy code) Works only for set number of cases.
    /*else {
            float slope = ps->y / ps->x ;
            //Finding the shortest distance between center of Mallet and line of travel for Puck(velocity vector of puck)
            float dist_Mxy_VPxy = abs(slope*mallet.x + (-1)*mallet.y + (puck.y - slope*puck.x)) / sqrt(slope*slope + (-1)*(-1));
            float dist_Mxy_Pxy =(float) getDistance(mallet,puck);
            //angle between path of puck and line joining the initial positions of puck and mallet.
            float theta = (float)asin(dist_Mxy_VPxy / dist_Mxy_Pxy) * 180/PI;
            //to find the distance between
            float dist_projectionMxy_Pxy = dist_Mxy_Pxy*cos(theta);
            float dist_collision = dist_projectionMxy_Pxy - MALLET_RADIUS - PUCK_RADIUS ;
            //to find the time taken for the puck to cover dist_collision
            float speed_puck = speed(*ps);
            float time_for_collision = dist_collision / speed_puck ;
            float speed_mallet = dist_Mxy_VPxy / time_for_collision;
            //finding the direction to shoot
            double shoot_theta = atan(-1 / slope) * 180/PI;centre_mallet,
            //cout << shoot_theta << " " << speed_mallet << " \n";
            ret.x = speed_mallet * cos(shoot_theta);
            ret.y = speed_mallet * sin(shoot_theta);

    }*/
    else{
        float time = 0.5;
        float theta_extra;//something
        Point centre_puck,reference_point;
        centre_puck.x= (puck.x + ps->x*time);
        centre_puck.y=(puck.y + ps->y*time);
        reference_point.x = centre_puck.x;
        reference_point.y = mallet.y;
        float distance_reference = reference_point.x - mallet.x;
        float distance_bw = getDistance(centre_puck,mallet);
        float ref_theta = acos(distance_reference/distance_bw)* 180/PI;
        //extrapolating position of puck
        //direction of mallet aiming at the extrapolated puck
        if(puck.x< 384 && mallet.x <= 384 && ps->x > 0  )
            ret.x = abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x < 384 && mallet.x > 384 && ps->x > 0)
            ret.x = MALLET_MAX_SPEED * cos(ref_theta);
        else if(puck.x > 384 && mallet.x <= 384 && ps->x > 0  )
            ret.x = abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x > 384 && mallet.x > 384 && ps->x > 0)
            ret.x = abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x< 384 && mallet.x <= 384 && ps->x < 0  )
            ret.x = -abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x < 384 && mallet.x > 384 && ps->x < 0)
            ret.x = -abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x > 384 && mallet.x <= 384 && ps->x < 0  )
            ret.x = -abs(MALLET_MAX_SPEED * cos(ref_theta));
        else if(puck.x > 384 && mallet.x > 384 && ps->x < 0)
            ret.x = -abs(MALLET_MAX_SPEED * cos(ref_theta));

            ret.y = abs(MALLET_MAX_SPEED * sin(ref_theta));
    }
    return ret;
}

int main(int argc, const char * argv[]) {
//while(1){
    Point p1;
    cout << "Enter Position for Mallet\n" ;
    cin >> p1.x ;
    cin >> p1.y ;

    Point p2;
    cout << "Enter Position for Puck\n" ;
    cin >> p2.x ;
    cin >> p2.y ;

    Velocity v;
    cout << "Enter Velocity for Puck\n" ;
    cin >> v.x ;
    cin >> v.y ;


    Velocity interception = intercept(p1, p2, &v);
    cout << "x: "<< interception.x << " y: " << interception.y;

    return 0;
}
