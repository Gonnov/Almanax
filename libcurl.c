#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
 
struct MemoryStruct {
  char *memory;
  size_t size;
};

char *final_string(struct MemoryStruct chunk)
{
    int i; 
    int j;
    char *found;
    char *daily_ressources;
    i = 12; //Number of characteres to avoid
    j = 0;
    found = strstr(chunk.memory, "Récupérer ");
    daily_ressources = malloc(64);


    while (found[i])
    {
      if (found[i] == ' ')
      {
        if (found[i+1] == 'e')
        {
          if (found[i+2] == 't')
          {
            daily_ressources[j] = '\0';
            return daily_ressources;
          }
        }
      }
      daily_ressources[j] = found[i];
      i++;
      j++;  
    }
    printf("the daily ressource wasn't find");
    return daily_ressources;
}
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
char *dailyneed_string(char *link)
{
  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);
  chunk.size = 0;
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, link);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  res = curl_easy_perform(curl_handle);
  char *daily_ressources = NULL;

  if(res != CURLE_OK) 
    fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
  else 
    daily_ressources = final_string(chunk);
 
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
  curl_global_cleanup();
  return daily_ressources;
}
