#include "Strategy.h"

const std::vector<StrategyItem> G_STRATEGIES = {
    // Discord
    {
        L"Discord",
        "discord",
        "Обход голосовых комнат, звонков и медиа-серверов",
        "--wf-tcp=80,443,2053,2083,2087,2096,8443 "
        "--wf-udp=443,19294-19344,50000-65535 "
        "--filter-udp=443,19294-19344,50000-65535 "
        "--dpi-desync=fake "
        "--dpi-desync-repeats=2 "
        "--dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" "
        "--dpi-desync-fake-discord=\"%BIN%quic_initial_www_google_com.bin\" "
        "--new "
        "--filter-tcp=2053,2083,2087,2096,8443 "
        "--dpi-desync=split2 "
        "--dpi-desync-split-pos=1 "
        "--new "
        "--filter-tcp=80,443 "
        "--hostlist=\"%LISTS%list-discord.txt\" "
        "--dpi-desync=fake,split2 "
        "--dpi-desync-split-pos=1 "
        "--dpi-desync-autottl=2 "
        "--dpi-desync-repeats=1 "
        "--dpi-desync-fooling=md5sig "
        "--dpi-desync-cutoff=d4 "
        "--dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\""
    },
    // Discord Standard
    {
        L"Discord standard",
        "discord_std",
        "Обновлённый Обход голосовых комнат, звонков и медиа-серверов",
        "--wf-tcp=80,443,2053,2083,2087,2096,8443 "
        "--wf-udp=443,19294-19344,50000-65535 "
        "--filter-udp=50000-65535 --dpi-desync=fake --dpi-desync-repeats=6 --dpi-desync-fake-discord=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-udp=19294-19344,50000-65535 --filter-l7=discord,stun --dpi-desync=fake --dpi-desync-fake-discord=\"%BIN%quic_initial_www_google_com.bin\" --dpi-desync-fake-stun=\"%BIN%quic_initial_www_google_com.bin\" --dpi-desync-repeats=6 --new "
        "--filter-tcp=2053,2083,2087,2096,8443 --hostlist-domains=discord.media --dpi-desync=multisplit --dpi-desync-split-seqovl=568 --dpi-desync-split-pos=1 --dpi-desync-split-seqovl-pattern=\"%BIN%tls_clienthello_www_google_com.bin\" --new "
        "--filter-tcp=80,443 --hostlist=\"%LISTS%list-discord.txt\" --dpi-desync=fake,multisplit --dpi-desync-split-seqovl=568 --dpi-desync-split-pos=1 --dpi-desync-fooling=badseq,md5sig --dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\""
    },
    // YouTube
    {
        L"YouTube",
        "youtube",
        "Стабильное воспроизведение роликов в 4к",
        "--wf-tcp=80,443 --wf-udp=443 "
        "--filter-udp=443 --hostlist-domains=googlevideo.com,youtube.com,ytimg.com,ggpht.com --dpi-desync=fake --dpi-desync-repeats=6 --dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-tcp=80,443 --hostlist-domains=googlevideo.com,youtube.com,ytimg.com,ggpht.com,gvt1.com --dpi-desync=fake,multisplit --dpi-desync-split-pos=midsld,1 --dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\" --dpi-desync-fooling=badseq,md5sig"
    },
    // YouTube Standard
    {
        L"YouTube standard",
        "youtube_std",
        "Обновлённое стабильное воспроизведение роликов в 4к",
        "--wf-tcp=80,443 "
        "--wf-udp=443 "
        "--filter-udp=443 "
        "--hostlist=\"%LISTS%list-youtube.txt\" "
        "--dpi-desync=fake "
        "--dpi-desync-repeats=8 "
        "--dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" "
        "--new "
        "--filter-tcp=80,443 "
        "--hostlist=\"%LISTS%list-youtube.txt\" "
        "--dpi-desync=fake,disorder2 "
        "--dpi-desync-split-pos=1 "
        "--dpi-desync-autottl=2 "
        "--dpi-desync-repeats=2 "
        "--dpi-desync-fooling=badseq,md5sig "
        "--dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\""
    },
    // Optimized standard
    {
        L"Optimized standard",
        "standard",
        "Стандартный режим для обход большинства веб-сайтов",
        "--wf-tcp=80,443,2053,2083,2087,2096,8443,1024-65535 "
        "--wf-udp=443,19294-19344,50000-50100,1024-65535 "
        "--filter-udp=443 --hostlist=\"%LISTS%list-general.txt\" --hostlist-exclude=\"%LISTS%list-exclude.txt\" --ipset-exclude=\"%LISTS%ipset-exclude.txt\" --dpi-desync=fake --dpi-desync-repeats=6 --dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-udp=19294-19344,50000-50100 --filter-l7=discord,stun --dpi-desync=fake --dpi-desync-fake-discord=\"%BIN%quic_initial_www_google_com.bin\" --dpi-desync-fake-stun=\"%BIN%quic_initial_www_google_com.bin\" --dpi-desync-repeats=6 --new "
        "--filter-tcp=2053,2083,2087,2096,8443 --hostlist-domains=discord.media --dpi-desync=multisplit --dpi-desync-split-seqovl=568 --dpi-desync-split-pos=1 --dpi-desync-split-seqovl-pattern=\"%BIN%tls_clienthello_4pda_to.bin\" --new "
        "--filter-tcp=443 --hostlist=\"%LISTS%list-google.txt\" --ip-id=zero --dpi-desync=multisplit --dpi-desync-split-seqovl=681 --dpi-desync-split-pos=1 --dpi-desync-split-seqovl-pattern=\"%BIN%tls_clienthello_www_google_com.bin\" --new "
        "--filter-tcp=80,443 --hostlist=\"%LISTS%list-general.txt\" --hostlist-exclude=\"%LISTS%list-exclude.txt\" --ipset-exclude=\"%LISTS%ipset-exclude.txt\" --dpi-desync=multisplit --dpi-desync-split-seqovl=568 --dpi-desync-split-pos=1 --dpi-desync-split-seqovl-pattern=\"%BIN%tls_clienthello_4pda_to.bin\" --new "
        "--filter-udp=443 --ipset=\"%LISTS%ipset-all.txt\" --hostlist-exclude=\"%LISTS%list-exclude.txt\" --ipset-exclude=\"%LISTS%ipset-exclude.txt\" --dpi-desync=fake --dpi-desync-repeats=6 --dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-tcp=80,443,1024-65535 --ipset=\"%LISTS%ipset-all.txt\" --hostlist-exclude=\"%LISTS%list-exclude.txt\" --ipset-exclude=\"%LISTS%ipset-exclude.txt\" --dpi-desync=multisplit --dpi-desync-split-seqovl=568 --dpi-desync-split-pos=1 --dpi-desync-split-seqovl-pattern=\"%BIN%tls_clienthello_4pda_to.bin\" --new "
        "--filter-udp=1024-65535 --ipset=\"%LISTS%ipset-all.txt\" --ipset-exclude=\"%LISTS%ipset-exclude.txt\" --dpi-desync=fake --dpi-desync-autottl=2 --dpi-desync-repeats=12 --dpi-desync-any-protocol=1 --dpi-desync-fake-unknown-udp=\"%BIN%quic_initial_www_google_com.bin\" --dpi-desync-cutoff=n2"
    },
    // Custom hosts
    {
        L"Custom hosts",
        "custom",
        "Обход по собственному списку пользовательских доменов",
        "--wf-tcp=80,443,2052,2053,2082,2083,2086,2087,2095,2096,8443 "
        "--wf-udp=443 "
        "--filter-udp=443 "
        "--hostlist=\"%FILES%custom-hosts.txt\" "
        "--dpi-desync=fake "
        "--dpi-desync-repeats=1 "
        "--dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" "
        "--new "
        "--filter-tcp=2052,2053,2082,2083,2086,2087,2095,2096,8443 "
        "--hostlist=\"%FILES%custom-hosts.txt\" "
        "--dpi-desync=split2 "
        "--dpi-desync-split-pos=1 "
        "--new "
        "--filter-tcp=80,443 "
        "--hostlist=\"%FILES%custom-hosts.txt\" "
        "--dpi-desync=fake,split2 "
        "--dpi-desync-split-pos=1 "
        "--dpi-desync-autottl=2 "
        "--dpi-desync-repeats=1 "
        "--dpi-desync-fooling=md5sig "
        "--dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\""
    },
    // Google & YouTube Full
    {
        L"Google services",
        "google_full",
        "Полный обход всех сервисов Google: YouTube, Google Drive, News, reCAPTCHA",
        "--wf-tcp=80,443 --wf-udp=443 "
        "--filter-udp=443 --hostlist=\"%LISTS%list-google.txt\" --dpi-desync=fake --dpi-desync-repeats=8 --dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-tcp=80,443 --hostlist=\"%LISTS%list-google.txt\" --dpi-desync=fake,multisplit --dpi-desync-split-pos=midsld,1 --dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\" --dpi-desync-fooling=badseq,md5sig --dpi-desync-autottl=2"
    },
    // Twitter / X
    {
        L"Twitter X",
        "twitter",
        "Полный обход Twitter X: лента, картинки, видео и медиа-сервера",
        "--wf-tcp=80,443 --wf-udp=443 "
        "--filter-udp=443 --hostlist=\"%LISTS%list-twitter.txt\" --dpi-desync=fake --dpi-desync-repeats=6 --dpi-desync-fake-quic=\"%BIN%quic_initial_www_google_com.bin\" --new "
        "--filter-tcp=80,443 --hostlist=\"%LISTS%list-twitter.txt\" --dpi-desync=fake,multisplit --dpi-desync-split-pos=midsld,1 --dpi-desync-fake-tls=\"%BIN%tls_clienthello_www_google_com.bin\" --dpi-desync-fooling=badseq,md5sig --dpi-desync-autottl=2"
    }
};

std::string GetStratsJson() {
    std::string json = "[";
    for (size_t i = 0; i < G_STRATEGIES.size(); ++i) {
        std::string titleStr(G_STRATEGIES[i].titleW.begin(), G_STRATEGIES[i].titleW.end());
        json.append("{\"title\":\"");
        json.append(titleStr);
        json.append("\",\"key\":\"");
        json.append(G_STRATEGIES[i].keyName);
        json.append("\",\"desc\":\"");
        json.append(G_STRATEGIES[i].desc);
        json.append("\"}");
        if (i + 1 < G_STRATEGIES.size()) {
            json.append(",");
        }
    }
    json.append("]");
    return json;
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string BuildStrategyCommandLine(const std::string& keyName, const fs::path& rootPath) {
    std::string binPath = (rootPath / "bin").string() + "\\";
    std::string listsPath = (rootPath / "lists").string() + "\\";
    std::string filesPath = (rootPath / "files").string() + "\\";

    std::string args = "";
    for (const auto& item : G_STRATEGIES) {
        if (item.keyName == keyName) {
            args = item.args;
            break;
        }
    }
    if (args.empty()) {
        args = G_STRATEGIES[0].args;
    }

    args = ReplaceAll(args, "%BIN%", binPath);
    args = ReplaceAll(args, "%LISTS%", listsPath);
    args = ReplaceAll(args, "%FILES%", filesPath);
    return args;
}