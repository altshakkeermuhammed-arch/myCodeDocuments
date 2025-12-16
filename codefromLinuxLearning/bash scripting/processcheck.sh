#!/bin/bash

#This shell shows Internet Status

clear
ping -c 3 www.google.com > /dev/null  2> /dev/null && echo "Internet is Working" || echo "Internet is not Working"

bc 
