#include "Logging.h"
#include "time.h"
#include "Temp_cleaner.h"

#include <unordered_set>
#include <fstream>
#include <string>
#include <filesystem>
#include <conio.h>
#include <iostream>


std::unordered_set<std::string> Blocklist = {
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

std::filesystem::path hosts_file = R"(C:\Windows\System32\drivers\etc\hosts)";
std::vector<std::string> all_host_lines;

bool is_elevated() {
    return  (std::filesystem::status(hosts_file).permissions() & std::filesystem::perms::owner_write) != std::filesystem::perms::none;
}

void block_analytics() {
    if(!is_elevated())
    {
        logging::log("Application not running with elevated privileges");
        return;
    }
    std::ifstream file(hosts_file);
    std::string line;
    while (std::getline(file, line)) {
        all_host_lines.push_back(line);
    }
    for (auto& item : Blocklist) {
        bool found = false;
        for (auto& hl : all_host_lines) {
            
            
            if (hl.find(item) != std::string::npos) {
                if(!hl.find("0.0.0.0 " + item))
                {
                    found = true;
                    logging::log("host " + item + " Detected Blocked Incorrectly Fixing");
                    all_host_lines.erase(std::remove(all_host_lines.begin(), all_host_lines.end(), hl), all_host_lines.end());
                    all_host_lines.push_back("0.0.0.0 " + item);
                    break;
                }
                found = true;
                logging::log("host " + item + " found");
                break;
            }
        }
        if (!found) {
            all_host_lines.push_back("0.0.0.0 " + item);
            logging::log("host " + item + " found");
        }
    }

    std::ofstream ofile(hosts_file);
    for (auto& hl : all_host_lines) {
        ofile << hl << std::endl;
    }
    ofile.close();
    logging::log("Analytics blocked successfully");
}



int main() {
    logging::log_init("logging started at ");
    logging::log("Vrchat Analytics Blocker"); logging::log("Press any key to continue...");
    _getch();
    block_analytics();
    logging::log("would you like to clear the temp hosts file? y/n");
    char c = _getch();
    if (c == 'y') {
        Temp_cleaner::delete_temp_files(Temp_cleaner::get_temp_folder());
        logging::log("hosts file cleared, Press any key to exit...");
        _getch();
    }
    return 0;
}

