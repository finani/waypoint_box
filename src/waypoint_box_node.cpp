
#include <stdio.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <ros/ros.h>


// setup the initial name
using namespace ros;
using namespace std;

void init_parameter(void);
void Waypoint_Publish(void);



Publisher  waypoint_pub;
std_msgs::Float32MultiArray  WP_msg;

float t_cur       = 0;
int   time_count  = 0;
int   wp_num      = 5;
float wp_time_sum = 0;
int   wp_ind      = 0;

float WayPoint_X[100];
float WayPoint_Y[100];
float WayPoint_Z[100];

float WayPoint_Roll[100];
float WayPoint_Pitch[100];
float WayPoint_Yaw[100];



// node main loop, for ROS
int main(int argc, char** argv)
{
    init(argc, argv, "waypoint_box_node");     // node name initialization
    NodeHandle nh_;                         // assign node handler

    printf("Initiate: waypoint_box_node\n");   // for debugging

    // Publish Topic
    waypoint_pub  = nh_.advertise<std_msgs::Float32MultiArray>("/box_weebee/cmd",10);

    Rate loop_rate(20);                      // setup the loop speed, [Hz]

    init_parameter();

    // node loop, for ROS, check ros status, ros::ok()
    while( ok() )
    {
        Waypoint_Publish();

        time_count++;
        t_cur = time_count/20.0;

        // loop rate [Hz]
        loop_rate.sleep();

        spinOnce();
    }

    // for debugging
    printf("Terminate: waypoint_box_node\n");

    return 0;
}

void init_parameter(void)
{
    wp_num = 5;
    float Way[wp_num][6] = {
        {  -3.0,   0.0,   5.0,   0.0,   0.0,    0.0 },
        {   1.0,   0.0,   5.0,   0.0,   0.0,   30.0 },
        {   2.0,   0.0,   5.0,   0.0,   0.0,  -30.0 },
        {   2.0,   1.0,   5.0,   0.0,   0.0,   30.0 },
        {   2.0,   2.0,   5.0,   0.0,   0.0,   60.0 },
    };

    for (int ind = 0; ind < wp_num; ind++)
    {
         WayPoint_X[ind] = Way[ind][0];
         WayPoint_Y[ind] = Way[ind][1];
         WayPoint_Z[ind] = Way[ind][2];
         WayPoint_Roll[ind] = Way[ind][3];
         WayPoint_Pitch[ind] = Way[ind][4];
         WayPoint_Yaw[ind] = Way[ind][5];
         std::cout << "[Waypoint] \t" << WayPoint_X[ind] << ", " << WayPoint_Y[ind] << ", " << WayPoint_Z[ind] << ", " << WayPoint_Roll[ind] << ", " << WayPoint_Pitch[ind] << ", " << WayPoint_Yaw[ind] << std::endl;
    }
    std::cout << std::endl;

    wp_time_sum = sqrt(pow(WayPoint_X[0], 2) + pow(WayPoint_Y[0], 2) + pow(WayPoint_Z[0], 2));
}

void Waypoint_Publish(void)
{
    if (t_cur > wp_time_sum *1.0) {
        wp_time_sum += sqrt(pow(WayPoint_X[wp_ind+1] - WayPoint_X[wp_ind], 2) + pow(WayPoint_Y[wp_ind+1] - WayPoint_Y[wp_ind], 2) + pow(WayPoint_Z[wp_ind+1] - WayPoint_Z[wp_ind], 2));
        wp_ind++;
    }

    WP_msg.data.resize(6);
    WP_msg.data[0] = WayPoint_X[wp_ind];
    WP_msg.data[1] = WayPoint_Y[wp_ind];
    WP_msg.data[2] = WayPoint_Z[wp_ind];
    WP_msg.data[3] = WayPoint_Roll[wp_ind];
    WP_msg.data[4] = WayPoint_Pitch[wp_ind];
    WP_msg.data[5] = WayPoint_Yaw[wp_ind];
    waypoint_pub.publish(WP_msg);
}
