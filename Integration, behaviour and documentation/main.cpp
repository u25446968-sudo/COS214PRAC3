#include <iostream>
#include "EventControl.h"
#include "EventGroup.h"
#include "EventUnit.h"

int main() {
    std::cout << " EventFlow: Pretoria Innovation Expo 2026\n";
  
    // Composite ownership tree: root -> halls -> zones -> leaves.
    EventGroup* expo = new EventGroup("Pretoria Innovation Expo");
    EventGroup* techHall = new EventGroup("Tech Hall");
    EventGroup* futureZone = new EventGroup("Future Mobility Zone");
    EventGroup* digitalZone = new EventGroup("Digital Futures Zone");
    EventGroup* communityHall = new EventGroup("Community Hall");

    DemoStage* keynoteStage = new DemoStage("Keynote Stage", 500);
    InnovationBooth* robotics = new InnovationBooth("Robotics Demo Booth", 80);
    InnovationBooth* aiLab = new InnovationBooth("AI Lab Booth", 100);
    InformationDesk* infoDesk = new InformationDesk("Visitor Information Desk", 20);
    ShuttleStop* shuttle = new ShuttleStop("Innovation Shuttle Stop", 120);
    SecurityTeam* security = new SecurityTeam("Tech Hall Security", 10);
    FoodVendor* cafe = new FoodVendor("Future Bites Vendor", 60);

    expo->add(techHall);
    expo->add(communityHall);
    techHall->add(futureZone);
    techHall->add(digitalZone);
    futureZone->add(keynoteStage);
    futureZone->add(robotics);
    digitalZone->add(aiLab);
    digitalZone->add(infoDesk);
    communityHall->add(shuttle);
    communityHall->add(security);
    communityHall->add(cafe);

    EventControl control;

    // Observer structure is intentionally separate from ownership.
    // Control -> Expo -> Tech Hall -> Future Zone -> leaves.
    control.attach(expo);
    expo->attach(techHall);
    expo->attach(communityHall);
    techHall->attach(futureZone);
    techHall->attach(digitalZone);
    communityHall->attach(shuttle);
    communityHall->attach(security);
    communityHall->attach(cafe);
    futureZone->attach(keynoteStage);
    futureZone->attach(robotics);
    digitalZone->attach(aiLab);
    digitalZone->attach(infoDesk);

    // Duplicate registration policy: duplicate is ignored.
    control.attach(expo);

    expo->open();

    std::cout << "\n--- Initial Composite traversal ---\n";
    expo->reportStatus();

    std::cout << "\n--- Notice 1: schedule change (cascade) ---\n";
    control.issueNotice(Notice(NoticeType::SCHEDULE_CHANGE,
                               "Keynote moved to 14:30", 1430));

    std::cout << "\n--- Notice 2: weather alert (polymorphic reactions) ---\n";
    control.issueNotice(Notice(NoticeType::WEATHER_ALERT,
                               "Thunderstorm approaching outdoor demonstration area"));

    std::cout << "\n--- Conditional capacity decision (alt in SD3) ---\n";
    control.evaluateCapacity(techHall, 600);

    std::cout << "\n--- Notice 3: transport delay ---\n";
    control.issueNotice(Notice(NoticeType::TRANSPORT_DELAY,
                               "Shuttle delayed by 15 minutes", 15));

    std::cout << "\n--- Runtime reorganisation: move vendor ---\n";
    EventComponent* movedCafe = communityHall->remove("Future Bites Vendor");
    if (movedCafe) {
        communityHall->detach(cafe);
        techHall->add(movedCafe);
        techHall->attach(cafe);
    }

    std::cout << "\n--- Registration change: security no longer receives community notices ---\n";
    communityHall->detach(security);
    // Missing detach is deliberately a no-op under the documented policy.
    communityHall->detach(security);

    std::cout << "\n--- Notice 4: evacuation ---\n";
    control.issueNotice(Notice(NoticeType::EVACUATE,
                               "Emergency evacuation initiated", 1));

    std::cout << "\n--- Registration change: security re-joins and receives resume ---\n";
    communityHall->attach(security);
    control.issueNotice(Notice(NoticeType::RESUME,
                               "Emergency cleared; normal operations may resume"));

    std::cout << "\n--- Original feature: stock alert ---\n";
    control.issueNotice(Notice(NoticeType::STOCK_ALERT,
                               "High-demand ingredient running low"));

    std::cout << "\n--- Clean shutdown: deleting root Composite ---\n";
    delete expo;
    std::cout << "[MAIN] Root deleted; owned subtree released exactly once.\n";
    std::cout << "[MAIN] EventFlow shutdown complete.\n";
    return 0;
}
