#!/bin/sh


#Fetches XML data to variable 'weatherdata'
weatherdata=`cat test.txt`
#Fetches Station code data(3-letter IATA format) to variable StationCode
StationCode=`cat Station.txt`

#echo $weatherdata
## Extract Weather data based on XML output

#Parse and fetches Temperature 
HTTemp=`echo $weatherdata | grep -E '(<temperature |/\\>)' | sed -e 's/^.*temperature value=\"//' -e 's/\".*$//'` 

#Parse and fetches Longitude 
Longi=`echo $weatherdata | grep -E '(<coord |/\\>)' | sed -e 's/^.*coord lon=\"//' -e 's/\".*$//'` 

#Parse and fetches Latitude 
Lat=`echo $weatherdata | grep -E '(<coord |/\\>)' | sed -e 's/^.*lat=\"//' -e 's/\".*$//'`


#Parse and fetches Condition 
#condition= `echo $weatherdata | grep -E '(<speed |/\\>)' | sed -e 's/^.*speed value=\"//' -e 's/\".*$//'`

#Parse and fetches Pressure
Pressure=`echo $weatherdata | grep -E '(<pressure |/\\>)' | sed -e 's/^.*pressure value=\"//' -e 's/\".*$//'`

#Parse and fetches Humidity
Humidity=`echo $weatherdata | grep -E '(<humidity |/\\>)' | sed -e 's/^.*humidity value=\"//' -e 's/\".*$//'`

#Parse and fetches Date & Time
DateTime=`echo $weatherdata | grep -E '(<lastupdate |/\\>)' | sed -e 's/^.*lastupdate value=\"//' -e 's/\".*$//'`

# Display Weather forecast informations
echo "$StationCode | $Longi , $Lat | $DateTime| $HTTemp °F| $Pressure hPa | $Humidity %"



