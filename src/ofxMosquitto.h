/*
 *  ofxMosquitto.h
 *  mosquittoExample
 *
 *  Created by James George on 11/3/11.
 *
 */

#pragma once

#include "ofMain.h"
#include "mosquittopp.h"

enum ofxMosquittoQoS {
	OF_MOSQ_QOS_0 = 0,
 	OF_MOSQ_QOS_1	= 1,
 	OF_MOSQ_QOS_2	= 2,
};

class ofxMosquittoSubscriber { 
  public:
	virtual void receivedMessage(const struct mosquitto_message* message) = 0;
	//TODO wrap other on_* functions
};

class ofxMosquitto : public mosquittopp::mosquittopp {
  public:
	ofxMosquitto(string id);
	~ofxMosquitto();
	
	void setSubscriber(ofxMosquittoSubscriber* subscriber);
	
	void setup(string host="localhost", int port=1883, int keepalive=60);
	void update();
	
	void subscribe(uint16_t* messageId, string topic, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_1);
	void subscribe(string topic, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_1);
	void unsubscribe(string topic);
	
	void publish(string topic, string message, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_1);
	void publish(string topic, uint32_t payloadlen, const uint8_t* payload, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_1);
	
  protected:
	ofxMosquittoSubscriber* subscriber;
	
	void on_connect(int rc);
	void on_disconnect();
	void on_publish(uint16_t mid);
	void on_message(const struct mosquitto_message *message);
	void on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos);
	void on_unsubscribe(uint16_t mid);
	void on_error();
	
		
};

