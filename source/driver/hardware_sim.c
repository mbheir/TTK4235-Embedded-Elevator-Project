#include <assert.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "hardware.h"

static int sockfd;
static pthread_mutex_t sockmtx;

int hardwareMovementToLegacy(HardwareMovement hardware_movement)
{
  switch (hardware_movement)
  {
    case HARDWARE_MOVEMENT_UP:
      return 1;
    case HARDWARE_MOVEMENT_DOWN:
      return -1;
    case HARDWARE_MOVEMENT_STOP:
      return 0;
    default:
      return 0;
  }
}

int hardwareOrderToLegacy(HardwareOrder hardware_order)
{
  switch (hardware_order)
  {
    case HARDWARE_ORDER_UP:
      return 0;
    case HARDWARE_ORDER_DOWN:
      return 1;
    case HARDWARE_ORDER_INSIDE:
      return 2;
    default:
      return -1;
  }
}


int hardwareInit() {
    char ip[16] = "localhost";
    char port[8] = "15657";

    pthread_mutex_init(&sockmtx, NULL);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1 && "Unable to set up socket");

    struct addrinfo hints = {
        .ai_family      = AF_INET,
        .ai_socktype    = SOCK_STREAM,
        .ai_protocol    = IPPROTO_TCP,
    };
    struct addrinfo* res;
    getaddrinfo(ip, port, &hints, &res);

    int fail = connect(sockfd, res->ai_addr, res->ai_addrlen);
    assert(fail == 0 && "Unable to connect to simulator server");

    freeaddrinfo(res);

    send(sockfd, (char[4]) {0}, 4, 0);

    return 0; //jalla
}




void hardwareCommandMovement(HardwareMovement movement) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {1, hardwareMovementToLegacy(movement)}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void hardwareCommandOrderLight(int floor, HardwareOrder order_type, int on) {
    assert(floor >= 0);
    assert(floor < HARDWARE_NUMBER_OF_FLOORS);
    assert(order_type >= 0);
    assert(order_type < HARDWARE_NUMBER_OF_BUTTONS);

    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {2, hardwareOrderToLegacy(order_type), floor, on}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void hardwareCommandFloorIndicatorOn(int floor) {
    assert(floor >= 0);
    assert(floor < HARDWARE_NUMBER_OF_FLOORS);

    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {3, floor}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void hardwareCommandDoorOpen(int door_open) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {4, door_open}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void hardwareCommandStopLight(int on) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {5, on}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}



int hardwareReadOrder(int floor, HardwareOrder order_type) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {6, hardwareOrderToLegacy(order_type), floor}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}


int hardwareReadFloorSensor(int floor) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {7}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1] ? buf[2] == floor : 0;
}


int hardwareReadStopSignal(void) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {8}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}


int hardwareReadObstructionSignal(void) {
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]) {9}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}