/*H**********************************************************************
* FILENAME :        WeatherFetch.c             
*
* DESCRIPTION :
*       Weather Forecast information fetch from Web server
*
* PUBLIC FUNCTIONS :
*       char *	handle_url(char* url)
*       size_t write_data(void *ptr, size_t size, 
*				size_t nmemb, struct url_data *data)
*
* NOTES :
*       Uses libcurl API for fetching weather data from web server
*	Uses OpenWeatherMap API (api.openweathermap.org)
*
* AUTHOR :    Renjith         	START DATE :    12 July 2016
*			  <Author>			<Date>			 DD-Month-Year
*
* CHANGES :
*
*H*/


#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "WeatherFetch.h"

/* URL Data */
struct url_data {
    size_t size;
    char* data;
};

/* Write Callback function definition */
size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif
    tmp = realloc(data->data, data->size + 1); 

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

/* Fetches HTTP URL Weather information */
char *handle_url(char* url) {
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = malloc(4096); /* reasonable size initial buffer */
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",  
                        curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    return data.data;
}

/*******************************************************************
 Overview	: Main Entry for Weather fetch application
 Args 		: argc & argv: Command line arguement 
 Input 		: <Application name> "Station Code"

********************************************************************/
int main(int argc, char* argv[]) {
    /* Stores Weather Data */
    char* Weatherdata;
    FILE *fp = fopen("Station.txt", "w");

    if(argc < 2) {
	printf(" \n");
        fprintf(stderr, "Provide City Name ID :WeatherFetch <City Name String> \n");
	printf(" Sydney :SYD \r\n Melbourne:MEL \r\n Adelaide:ADL \r\n");
	printf(" Canberra:CBR \r\n Tasmania:TAS \r\n Hamilton:HLT \r\n");
	printf(" Kempsey:KPS \r\n New Castle:NTL \r\n Perth:PER \r\n Maryborough:MBH \r\n");
        return 1;
    }

    if(strcmp(argv[1],"SYD")==0){
	strcpy(argv[1],URL_SYD);
	if(fp != NULL){
		fprintf(fp,"%s","SYD");
	}
    }
    else if(strcmp(argv[1],"MEL")==0){
	strcpy(argv[1],URL_MEL);
	if(fp != NULL){
		fprintf(fp,"%s","MEL");
	}
    }
    else if(strcmp(argv[1],"ADL")==0){
	strcpy(argv[1],URL_ADL);
	if(fp != NULL){
		fprintf(fp,"%s","ADL");
	}
    }
    else if(strcmp(argv[1],"CBR")==0){
	strcpy(argv[1],URL_CBR);
		if(fp != NULL){
		fprintf(fp,"%s","CBR");
	}
    }
    else if(strcmp(argv[1],"TAS")==0){
	strcpy(argv[1],URL_TAS);
	if(fp != NULL){
		fprintf(fp,"%s","TAS");
	}
    }
    else if(strcmp(argv[1],"HLT")==0){
	strcpy(argv[1],URL_HLT);
	if(fp != NULL){
		fprintf(fp,"%s","HLT");
	}
    }
    else if(strcmp(argv[1],"KPS")==0){
	strcpy(argv[1],URL_KPS);
			if(fp != NULL){
		fprintf(fp,"%s","KPS");
	}
    }
    else if(strcmp(argv[1],"NTL")==0){
	strcpy(argv[1],URL_NTL);
	if(fp != NULL){
		fprintf(fp,"%s","NTL");
	}
    }
    else if(strcmp(argv[1],"PER")==0){
	strcpy(argv[1],URL_PER);
	if(fp != NULL){
		fprintf(fp,"%s","PER");
	}
    }
    else if(strcmp(argv[1],"MBH")==0){
	strcpy(argv[1],URL_MBH);
	if(fp != NULL){
		fprintf(fp,"%s","MBH");
	}
	
    }
    else{
	printf("Invalid Station or Station Unavailable !!!!\n");
	fclose(fp);
	return 1;
    }
    fclose(fp);

    Weatherdata = handle_url(argv[1]);

    if(Weatherdata) {

	FILE *fptr = fopen("test.txt", "w+");
	if (fptr == NULL)
	{
    		printf("Error opening file!\n");
    		exit(1);
	}
	fprintf(fptr,"%s",Weatherdata);
  	fclose(fptr);
	

        free(Weatherdata);
    }
	/* Launch Shell script for parsing and displaying Weather data */
	system("$PWD/GetUrl.sh");
    return 0;
}
