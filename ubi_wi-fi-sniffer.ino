#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <base64.h>
#include <map>

// WiFi 配置
const char* ssid = "your_wifi_ssid";           // WiFi SSID
const char* password = "your_wifi_password";    // WiFi 密码

// WordPress REST API 配置
const char* wordpressHost = "https://yourwordpresssite.com";  // WordPress 网址
const char* wordpressPostEndpoint = "/wp-json/wp/v2/posts";   // WordPress API 端点

// 用户名和应用密码
const char* username = "your_api_username";       // API 用户名
const char* app_password = "your_api_password";   // API 应用密码

// 信号强度阈值
const int signalThreshold = -70;  // 将-70dBm以上的设备视为高信号设备
bool isHome = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // 连接到 WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
}

void loop() {
  scanWiFiAndCategorizeDevices();
  delay(300000);  // 每5分钟执行一次
}

void scanWiFiAndCategorizeDevices() {
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete.");

  String highSignalDevices = "High Signal Devices (Above -70 dBm):\\n";
  String lowSignalDevices = "Low Signal Devices (Below -70 dBm):\\n";
  int highSignalCount = 0;
  int lowSignalCount = 0;

  for (int i = 0; i < n; ++i) {
    String bssid = WiFi.BSSIDstr(i); // 获取设备的 MAC 地址
    int rssi = WiFi.RSSI(i);         // 获取信号强度

    // 分类设备为高信号或低信号
    if (rssi > signalThreshold) {
      highSignalDevices += "MAC: " + bssid + ", Signal: " + String(rssi) + " dBm\\n";
      highSignalCount++;
    } else {
      lowSignalDevices += "MAC: " + bssid + ", Signal: " + String(rssi) + " dBm\\n";
      lowSignalCount++;
    }
  }

  // 生成状态信息并上传
  String statusMessage = "Estimated number of people (High Signal): " + String(highSignalCount) + "\\n" + highSignalDevices + "\\n" +
                         "Other Devices Detected: " + String(lowSignalCount) + "\\n" + lowSignalDevices;
  postToWordPress(statusMessage);
}

void postToWordPress(String statusMessage) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();  // 忽略证书验证（测试用，实际使用中请添加证书验证）

    HTTPClient http;
    String url = String(wordpressHost) + String(wordpressPostEndpoint);
    http.begin(client, url);

    // 运行时生成 Base64 编码的认证字符串
    String auth = String(username) + ":" + String(app_password);
    String authEncoded = "Basic " + base64::encode(auth);

    // 设置 HTTP 头部
    http.addHeader("Authorization", authEncoded);
    http.addHeader("Content-Type", "application/json");

    // 构建 JSON 请求体，包含在家状态
    String payload = "{\"title\":\"Wi-Fi Sniffer\",\"content\":\"" + statusMessage + "\",\"status\":\"publish\"}";

    // 发送 POST 请求
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode == 201) {
      Serial.println("Success: Post created on WordPress.");
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      Serial.println("Error message: ");
      Serial.println(http.getString());  // 打印服务器的错误信息，帮助调试
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
