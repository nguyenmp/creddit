#include <stdio.h>
#include <curl/curl.h>

int main() {
  // Initialize curl and do some sanity checks
  CURL* curl = curl_easy_init();
  if (curl == NULL) {
    printf("ERROR: Could not start up CURL\n");
    return 1;
  }

  curl_easy_setopt(curl, CURLOPT_URL, "http://www.reddit.com/.json");
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  curl_easy_perform(curl);

  return 0;
}
