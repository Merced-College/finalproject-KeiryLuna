#pragma once
#include <string>
#include <vector>
#include "json.hpp"

class appointment {
private:
    int id;
    int customerId;
    std::string customerName;
    std::string date;        // format: "YYYY-MM-DD"
    std::string time;        // format: "HH:MM"
    std::string serviceType;
    std::string notes;
    bool isCompleted;

public:
    // constructor
    appointment(int id, int customerId, std::string customerName, std::string date, std::string time, std::string serviceType, std::string notes = "");

    // getters
    int getId() const { return id; }
    int getCustomerId() const { return customerId; }
    std::string getCustomerName() const { return customerName; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    std::string getServiceType() const { return serviceType; }
    std::string getNotes() const { return notes; }
    bool getIsCompleted() const { return isCompleted; }

    // setters
    void markCompleted()                     { isCompleted = true; }
    void setNotes(std::string n)             { notes = n; }
    void setDate(std::string d)              { date = d; }
    void setTime(std::string t)              { time = t; }

    // ── conflict detection algorithm ──────────────
    // checks if this appointment conflicts with another
    bool conflictsWith(const appointment& other) const;

    // static search functions
    static std::vector<appointment> getByDate(std::vector<appointment>& appointments, std::string date);
    static std::vector<appointment> getByCustomer(std::vector<appointment>& appointments, int customerId);
    static bool hasConflict(std::vector<appointment>& appointments, std::string date, std::string time);

    // JSON for frontend
    nlohmann::json toJson() const;
};