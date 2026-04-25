#include "appointment.h"
#include <iostream>

appointment::appointment(int id, int customerId, std::string customerName, std::string date, std::string time, std::string serviceType, std::string notes)
    : id(id), customerId(customerId), customerName(customerName),
      date(date), time(time), serviceType(serviceType),
      notes(notes), isCompleted(false) {}

// ── conflict detection algorithm ──────────────────────
// checks if two appointments are on the same date and time
// Big-O: O(1) — just compares two values
bool appointment::conflictsWith(const appointment& other) const {
    return (date == other.date && time == other.time);
}

// ── get all appointments for a specific date ──────────
// Big-O: O(n) — loops through all appointments
std::vector<appointment> appointment::getByDate(std::vector<appointment>& appointments,std::string date) {
    std::vector<appointment> result;

    for (auto& a : appointments) {        // loop through all
        if (a.getDate() == date) {        // check if date matches
            result.push_back(a);          // add to results
        }
    }
    return result;
}


// ── get all appointments for a specific customer ──────
// Big-O: O(n) — loops through all appointments
std::vector<appointment> appointment::getByCustomer(std::vector<appointment>& appointments,int customerId) {
    std::vector<appointment> result;

    for (auto& a : appointments) {
        if (a.getCustomerId() == customerId) {
        result.push_back(a);
        }
    }
    return result;
}


// ── conflict detection ────────────────────────────────
// checks if ANY existing appointment conflicts with new date/time
// Big-O: O(n) — must check every appointment
bool appointment::hasConflict(std::vector<appointment>& appointments, std::string date, std::string time) {
    for (auto& a : appointments) {        // loop through every appointment
        if (a.getDate() == date && a.getTime() == time && !a.getIsCompleted()) {
            return true;
        }                       
    }
    return false;                         
}

// ── JSON for frontend ─────────────────────────────────
nlohmann::json appointment::toJson() const {
    return nlohmann::json{
        {"id",           id},
        {"customerId",   customerId},
        {"customerName", customerName},
        {"date",         date},
        {"time",         time},
        {"serviceType",  serviceType},
        {"notes",        notes},
        {"isCompleted",  isCompleted}
    };
}