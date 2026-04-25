#include "httplib.h"
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "profitCalculator.h"
#include "customer.h"
#include "quote.h"
#include "ExpenseTracker.h"
#include "Expense.h"
#include "invoices.h"
#include "Employee.h"
#include "appointment.h"
#include "dataManager.h"          // ← added

using json = nlohmann::json;

// ── globals ───────────────────────────────────────────
dataManager      dm;               // ← added
ExpenseTracker   expTracker;

std::vector<customer>    customers;
std::vector<quote>       quotes;
std::vector<invoices>    invoiceList;
std::vector<Employee>    employees;
std::vector<appointment> appointments;

int nextCustomerId    = 1;
int nextQuoteId       = 1;
int nextInvoiceId     = 1;
int nextEmployeeId    = 1;
int nextAppointmentId = 1;

// ── read file helper ──────────────────────────────────
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// ── set next IDs from loaded data ─────────────────────
void setNextIds() {
    for (auto& c : customers)
        if (c.getId() >= nextCustomerId)
            nextCustomerId = c.getId() + 1;

    for (auto& q : quotes)
        if (q.id >= nextQuoteId)
            nextQuoteId = q.id + 1;

    for (auto& inv : invoiceList)
        if (inv.id >= nextInvoiceId)
            nextInvoiceId = inv.id + 1;

    for (auto& e : employees)
        if (e.getId() >= nextEmployeeId)
            nextEmployeeId = e.getId() + 1;

    for (auto& a : appointments)
        if (a.getId() >= nextAppointmentId)
            nextAppointmentId = a.getId() + 1;
}

int main() {
    httplib::Server svr;

    // ── load all data on startup using dataManager ────
    customers    = dm.loadCustomers("customer.csv");
    quotes       = dm.loadQuotes("quote.csv");
    invoiceList  = dm.loadInvoices("invoices.csv");
    employees    = dm.loadEmployees("employees.csv");
    appointments = dm.loadAppointments("appointments.csv");
    dm.loadExpenses("expenses.csv", expTracker);

    // set correct next IDs
    setNextIds();

    svr.set_default_headers({
        {"Access-Control-Allow-Origin",  "*"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });

    // ── serve pages ───────────────────────────────────
    //Index 2
    svr.Get("/", [](auto& req, auto& res) {
        res.set_content(readFile("../FrontEnd/index2.html"), "text/html");
    });

    svr.Get("/index2.html", [](auto& req, auto& res) {
        res.set_content(readFile("../FrontEnd/index2.html"), "text/html");
    });

    //Employees page
    svr.Get("/employees.html", [](auto& req, auto& res) {
        res.set_content(readFile("../FrontEnd/employees.html"), "text/html");
    });

    svr.Get("/employees", [](auto& req, auto& res) {
        res.set_content(readFile("../FrontEnd/employees.html"), "text/html");
    });

    //Customers page
    svr.Get("/customers", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/customers.html"), "text/html");
    });

    svr.Get("/customers.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/customers.html"), "text/html");
    });

    svr.Get("/customers.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/customers.css"), "text/css");
    });

     svr.Get("/customers.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/customers.js"), "text/javascript");
    });

    //Appointment page
    svr.Get("/appointment", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/appointment.html"), "text/html");
    });

    svr.Get("/appointment.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/appointment.html"), "text/html");
    });

    svr.Get("/appointment.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/appointment.css"), "text/css");
    });

    svr.Get("/appointment.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/appointment.js"), "text/javascript");
    });

    //Invoices page
     svr.Get("/invoices", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/invoices.html"), "text/html");
    });

    svr.Get("/invoices.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/invoices.html"), "text/html");
    });

    svr.Get("/invoices.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/invoices.css"), "text/css");
    });

    svr.Get("/invoices.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/invoices.js"), "text/javascript");
    });

    //Quote Page
    svr.Get("/quote", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/quote.html"), "text/html");
    });

    svr.Get("/quote.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/quote.html"), "text/html");
    });

    svr.Get("/quote.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/quote.css"), "text/css");
    });

    svr.Get("/quote.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/quote.js"), "text/javascript");
    });

    //Expense Page
     svr.Get("/expense", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/expense.html"), "text/html");
    });

    svr.Get("/expense.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/expense.html"), "text/html");
    });

    svr.Get("/expense.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/expense.css"), "text/css");
    });

    svr.Get("/expense.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/expense.js"), "text/javascript");
    });

    //profitCalculator Page
    svr.Get("/profitCalculator", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/profitCalculator.html"), "text/html");
    });

    svr.Get("/profitCalculator.html", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/profitCalculator.html"), "text/html");
    });

    svr.Get("/profitCalculator.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/profitCalculator.css"), "text/css");
    });

    svr.Get("/profitCalculator.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/profitCalculator.js"), "text/javascript");
    });


    //

    svr.Get("/style.css", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/style.css"), "text/css");
    });

    svr.Get("/script.js", [](auto& req, auto& res) {
    res.set_content(readFile("../FrontEnd/script.js"), "text/javascript");
    });

    // ── expenses ──────────────────────────────────────
    svr.Get("/api/expenses", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& e : expTracker.getAllExpenses())
            result.push_back(e.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/expenses", [&](auto& req, auto& res) {
        auto body = json::parse(req.body);
        expTracker.addExpense(
            body["amount"],
            body["category"],
            body["date"],
            body["description"]
        );
        dm.saveExpenses("expenses.csv", expTracker);  // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Get("/api/expenses/category/(\\w+)", [&](auto& req, auto& res) {
        std::string category = req.matches[1];
        json result;
        result["category"] = category;
        result["total"]    = expTracker.getTotalByCategory(category);
        res.set_content(result.dump(), "application/json");
    });

    svr.Get("/api/expenses/month/(\\d{4}-\\d{2})", [&](auto& req, auto& res) {
        std::string yearMonth = req.matches[1];
        json result;
        result["month"] = yearMonth;
        result["total"] = expTracker.getTotalExpensesByMonth(yearMonth);
        res.set_content(result.dump(), "application/json");
    });

    // ── customers ─────────────────────────────────────
    svr.Get("/api/customers", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& c : customers)
            result.push_back(c.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/customers", [&](auto& req, auto& res) {
        auto body = json::parse(req.body);
        customer c(
            nextCustomerId++,
            body["name"],
            body["phone"],
            body["email"],
            body["address"]
        );
        customers.push_back(c);
        dm.saveCustomers("customer.csv", customers);  // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Delete("/api/customers/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        customers.erase(
            std::remove_if(customers.begin(), customers.end(),
                [id](customer& c) { return c.getId() == id; }),
            customers.end());
        dm.saveCustomers("customer.csv", customers);  // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Get("/api/customers/search/(.*)", [&](auto& req, auto& res) {
        std::string query = req.matches[1];
        json result = json::array();
        for (auto& c : customers) {
            if (c.getName().find(query)  != std::string::npos ||
                c.getPhone().find(query) != std::string::npos) {
                result.push_back(c.toJson());
            }
        }
        res.set_content(result.dump(), "application/json");
    });

    // ── profit calculator ─────────────────────────────
    svr.Post("/api/profit", [](auto& req, auto& res) {
        auto body = json::parse(req.body);
        profitCalculator calc;
        calc.amountCharged = body["amountCharged"];
        calc.supplyCost    = body["supplyCost"];
        calc.laborHours    = body["laborHours"];
        calc.laborRate     = body["laborRate"];
        json result;
        result["laborCost"]     = calc.calcLaborCost();
        result["profit"]        = calc.calculateProfit();
        result["wasProfitable"] = calc.wasProfitable();
        res.set_content(result.dump(), "application/json");
    });

    // ── quotes ────────────────────────────────────────
    svr.Get("/api/quotes", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& q : quotes) {
            result.push_back({
                {"id",              q.id},
                {"customerName",    q.customerName},
                {"customerPhone",   q.customerPhone},
                {"serviceType",     q.serviceType},
                {"vehicleDesc",     q.vehicleDesc},
                {"date",            q.date},
                {"supplyCost",      q.supplyCost},
                {"laborHours",      q.laborHours},
                {"laborRate",       q.laborRate},
                {"amountCharged",   q.amountCharged},
                {"estimatedProfit", q.estimatedProfit()},
                {"notes",           q.notes}
            });
        }
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/quotes", [&](auto& req, auto& res) {
        auto body = json::parse(req.body);
        quote q;
        q.id            = nextQuoteId++;
        q.customerName  = body["customerName"];
        q.customerPhone = body["customerPhone"];
        q.serviceType   = body["serviceType"];
        q.vehicleDesc   = body["vehicleDesc"];
        q.date          = body["date"];
        q.supplyCost    = body["supplyCost"];
        q.laborHours    = body["laborHours"];
        q.laborRate     = body["laborRate"];
        q.amountCharged = body["amountCharged"];
        q.notes         = body["notes"];
        quotes.push_back(q);
        dm.saveQuotes("quote.csv", quotes);          // ← dataManager
        json result;
        result["success"]         = true;
        result["id"]              = q.id;
        result["estimatedProfit"] = q.estimatedProfit();
        res.set_content(result.dump(), "application/json");
    });

    // ── invoices ──────────────────────────────────────
    svr.Get("/api/invoices", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& inv : invoiceList)
            result.push_back(inv.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/invoices", [&](auto& req, auto& res) {
        auto body = json::parse(req.body);
        invoices newInv(
            nextInvoiceId++,
            body["customerId"],
            body["customerName"],
            body["date"],
            body["amount"],
            body.value("isPaid", false)
        );
        invoiceList.push_back(newInv);
        dm.saveInvoices("invoices.csv", invoiceList); // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Put("/api/invoices/pay/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        for (auto& inv : invoiceList) {
            if (inv.id == id) {
                inv.isPaid = true;
                dm.saveInvoices("invoices.csv", invoiceList); // ← dataManager
                return res.set_content(
                    "{\"success\": true}", "application/json");
            }
        }
        res.status = 404;
        res.set_content(
            "{\"error\": \"Invoice not found\"}", "application/json");
    });

    // ── employees ─────────────────────────────────────
    svr.Get("/api/employees", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& e : employees)
            result.push_back(e.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/employees", [&](auto& req, auto& res) {
        auto body = json::parse(req.body);
        Employee e(
            nextEmployeeId++,
            body["name"],
            body["jobType"],
            body["hourlyRate"],
            body["phone"],
            body["email"]
        );
        employees.push_back(e);
        dm.saveEmployees("employees.csv", employees); // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Delete("/api/employees/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        employees.erase(
            std::remove_if(employees.begin(), employees.end(),
                [id](Employee& e) { return e.getId() == id; }),
            employees.end());
        dm.saveEmployees("employees.csv", employees); // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    svr.Get("/api/employees/search/(.*)", [&](auto& req, auto& res) {
        std::string query = req.matches[1];
        Employee* found = Employee::searchByName(employees, query);
        if (found) {
            res.set_content(found->toJson().dump(), "application/json");
        } else {
            res.set_content("{\"found\": false}", "application/json");
        }
    });

    svr.Put("/api/employees/hours/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        auto body = json::parse(req.body);
        for (auto& e : employees) {
            if (e.getId() == id) {
                e.addHours(body["hours"]);
                dm.saveEmployees("employees.csv", employees); // ← dataManager
                json result;
                result["success"]     = true;
                result["totalPay"]    = e.calculatePay();
                result["hoursWorked"] = e.getHoursWorked();
                return res.set_content(result.dump(), "application/json");
            }
        }
        res.status = 404;
        res.set_content(
            "{\"error\": \"Employee not found\"}", "application/json");
    });

    // ── appointments ──────────────────────────────────
    svr.Get("/api/appointments", [&](auto& req, auto& res) {
        json result = json::array();
        for (auto& a : appointments)
            result.push_back(a.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Get("/api/appointments/date/(.*)", [&](auto& req, auto& res) {
        std::string date = req.matches[1];
        auto filtered = appointment::getByDate(appointments, date);
        json result = json::array();
        for (auto& a : filtered)
            result.push_back(a.toJson());
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/appointments", [&](auto& req, auto& res) {
    auto body = json::parse(req.body);

    std::string date = body["date"];   // ← get date
    std::string time = body["time"];   // ← get time

    // conflict detection
    if (appointment::hasConflict(appointments, date, time)) {
        res.status = 409;
        res.set_content(
            "{\"error\": \"Time slot already booked\"}",
            "application/json");
        return;
    }

    appointment a(
        nextAppointmentId++,
        body["customerId"],
        body["customerName"],
        date,                          // ← date first 
        time,                          // ← time second 
        body["serviceType"],
        body.value("notes", "")
    );

    appointments.push_back(a);
    dm.saveAppointments("appointments.csv", appointments);

    json result;
    result["success"] = true;
    result["id"]      = a.getId();
    res.set_content(result.dump(), "application/json");
    });

    svr.Put("/api/appointments/complete/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        for (auto& a : appointments) {
            if (a.getId() == id) {
                a.markCompleted();
                dm.saveAppointments("appointments.csv", appointments); // ← dataManager
                return res.set_content(
                    "{\"success\": true}", "application/json");
            }
        }
        res.status = 404;
        res.set_content("{\"error\": \"Not found\"}", "application/json");
    });

    svr.Delete("/api/appointments/(\\d+)", [&](auto& req, auto& res) {
        int id = std::stoi(req.matches[1]);
        appointments.erase(
            std::remove_if(appointments.begin(), appointments.end(),
                [id](appointment& a) { return a.getId() == id; }),
            appointments.end());
        dm.saveAppointments("appointments.csv", appointments); // ← dataManager
        res.set_content("{\"success\": true}", "application/json");
    });

    std::cout << "Server running at http://localhost:8080\n";
    svr.listen("localhost", 8080);
    return 0;
}
