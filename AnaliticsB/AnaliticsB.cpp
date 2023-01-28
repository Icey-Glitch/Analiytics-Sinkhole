
#include <iostream>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>





std::vector<std::string> Blocklist = {
    // VRChat
    "api.amplitude.com",
    "api2.amplitude.com",
    "cdn.amplitude.com",
    // Unity
    "api.uca.cloud.unity3d.com",
    "config.uca.cloud.unity3d.com",
    "cdp.cloud.unity3d.com",
    "data-optout-service.uca.cloud.unity3d.com",
    "perf-events.cloud.unity3d.com",
    "public.cloud.unity3d.com",
    "ecommerce.iap.unity3d.com",
    "remote-config-proxy-prd.uca.cloud.unity3d.com",
    "thind-gke-euw.prd.data.corp.unity3d.com",
    "thind-gke-usc.prd.data.corp.unity3d.com",
    "thind-gke-ape.prd.data.corp.unity3d.com",
    // DBD
    "gamelogs.live.bhvrdbd.com",
    "rtm.live.dbd.bhvronline.com",
    // Genshin Impact
    "log-upload-os.mihoyo.com",
    // Redshell 
    "api.gameanalytics.com",
    "files.facepunch.com",
    "in.treasuredata.com",
    "api.redshell.io",
    "rubick.gameanalytics.com",
    // Just Cause
    "nelo2-col.nhncorp.jp",
    // GoG Galaxy
    "galaxy-client-reports.gog.com",
    "insights-collector.gog.com",
    "gwent-bi-collector.gog.com",
    // Google
    "stats.g.doubleclick.net",
    // Steam
    "crash.steampowered.com",
    // Solarwinds
    "logs-01.loggly.com",
    // Vermintide
    "5fs-crashify.s3-accelerate.amazonaws.com",
    // China Analytics
    "crashlogs.woniu.com",
    // Microsoft
    "vortex.data.microsoft.com"
};

void BlockAnalytics() {
    std::string HostsFile = "C:\\Windows\\System32\\drivers\\etc\\hosts";
    std::vector<std::string> AllHostLines;

    std::ifstream file(HostsFile);
    std::string line;
    while (std::getline(file, line))
        AllHostLines.push_back(line);

    file.close();

    for (auto& url : Blocklist) {
        bool IsExisting = false;
        for (auto& line : AllHostLines) {
            if (line.find(url) != std::string::npos) {
                IsExisting = true;
                break;
            }
        }

        if (!IsExisting) {
            AllHostLines.push_back("127.0.0.1 " + url);
        }
    }

    std::ofstream outfile(HostsFile);
    for (auto& line : AllHostLines)
        outfile << line << std::endl;

    outfile.close();
}

int main(int argc, char* argv[])
{
    std::cout << "Vrchat Analytics Blocker" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();
    BlockAnalytics();
    return 0;
}
