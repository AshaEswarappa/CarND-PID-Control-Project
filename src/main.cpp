#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"


// for convenience
using nlohmann::json;
using namespace std;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() 
{
  uWS::Hub h;

  /*PID controller for steering angle */
  PID pid;

  
  /**
   * TODO: Initialize the pid variable.
   */
    pid.Init(0.14, 0.0, 0.99); //for steering angle 

    /*Only for P Controller */
    //pid.Init(0.5, 0.0, 0.0);

    /*Only for I-Controller */
    //pid.Init(0.0, 0.5, 0.0);

    /*Only for D Controller */
    //pid.Init(0.0, 0.0, 1.0);


  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = stod(j[1]["cte"].get<string>());
          double speed = stod(j[1]["speed"].get<string>());
          double angle = stod(j[1]["steering_angle"].get<string>());
          double steer_value = 0;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */

            pid.UpdateError(cte); //update the cross track error for steering angle

            steer_value = pid.TotalError(); // get the PID controller error

            if (steer_value > 1)
            {
              steer_value = 1; // limit to maximum allowed steering angle
            }

            if (steer_value < -1)
            {
              steer_value = -1; // limit to minimum allowed steering angle
            }

            /*Speed PID controller */
            /*PID controller for Speed */
            PID speed_pid;

            speed_pid.Init(0.115, 0.0, 0.0); //Initializing the speed PID controller

            double TARGET_SPEED = 36.50; // target speed of the vehicle

            double throttle_value = 0.0; // controller ouput for speed

            double error = speed - TARGET_SPEED; // error for speed controller

            speed_pid.UpdateError(error); // updated error

            throttle_value = speed_pid.TotalError(); // controller output of speed

            if (throttle_value > 1.0)
            {
              throttle_value = 1.0; // limit to maximum allowed throttle
            } 
            
            if (throttle_value < -1.0)
            {
              throttle_value = -1.0; // limit to minimum allowed steering angle
            }


        
          // DEBUG
          cout << "CTE: " << cte << " Steering Value: " << steer_value 
                    << endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value; // tried to keep the same value i.e..close to 0.3 but using a PID controller
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          cout << msg << endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    cout << "Connected!!!" << endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    cout << "Disconnected" << endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    cout << "Listening to port " << port << endl;
  } else {
    cerr << "Failed to listen to port" << endl;
    return -1;
  }
  
  h.run();
}