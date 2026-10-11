#pragma once

#include <filesystem>
#include <string>

namespace pt {

// Crash reports sent to the developer (Sentry's minidump endpoint), only with the player's consent.
//
// The log of a session that crashed is rewritten by the next start, so PreserveCrashLog runs before the log file is opened: a
// crash dump (pt-crash-*.dmp, crash_report.h) newer than pt.log's last write and without a log of its own gets pt.log copied
// next to it (pt-crash-*.log). OfferCrashUpload then asks once per dump whether to send it (Send, Don't send, Always send);
// the answer "always" is kept in crash-reports.txt in the same folder. A dump that was sent or declined gets a .sent or .skip
// file and is not asked about again. The upload runs on its own thread.
void PreserveCrashLog(const std::filesystem::path& log_path);
void OfferCrashUpload(const std::filesystem::path& dir, const std::string& version, bool interactive);

}
