#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "WeatherFetch.h"

struct url_data {
    size_t size;
    char* data;
};

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

int main(int argc, char* argv[]) {
    /* Stores Weather Data */
    char* Weatherdata;

    if(argc < 2) {
	printf(" \n");
        fprintf(stderr, "Provide City Name ID :WeatherFetch <City Name String> \n");
	printf(" Sydney :SYD \r\n Melbourne:MEL \r\n Adelaide:ADL \r\n");
	printf(" QueensLand:QLD \r\n Tasmania:TAS \r\n Victoria:VIC \r\n");
	printf(" Kempsey:KPS \r\n New Castle:NTL \r\n Perth:PER \r\n Maryborough:MBH \r\n");
        return 1;
    }

    if(strcmp(argv[1],"SYD")==0){
	strcpy(argv[1],URL_SYD);
    }
    else if(strcmp(argv[1],"MEL")==0){
	strcpy(argv[1],URL_MEL);
    }
    else if(strcmp(argv[1],"ADL")==0){
	strcpy(argv[1],URL_ADL);
    }
    else if(strcmp(argv[1],"QLD")==0){
	strcpy(argv[1],URL_QLD);
    }
    else if(strcmp(argv[1],"TAS")==0){
	strcpy(argv[1],URL_TAS);
    }
    else if(strcmp(argv[1],"VIC")==0){
	strcpy(argv[1],URL_VIC);
    }
    else if(strcmp(argv[1],"KPS")==0){
	strcpy(argv[1],URL_KPS);
    }
    else if(strcmp(argv[1],"NTL")==0){
	strcpy(argv[1],URL_NTL);
    }
    else if(strcmp(argv[1],"PER")==0){
	strcpy(argv[1],URL_PER);
    }
    else if(strcmp(argv[1],"MBH")==0){
	strcpy(argv[1],URL_MBH);
    }
    else{
	printf("Invalid Station or Station Unavailable !!!!\n");
	return 1;
    }
    Weatherdata = handle_url(argv[1]);
    

    if(Weatherdata) {
        printf(" %s \n", Weatherdata);
        free(Weatherdata);
    }

    return 0;
}
