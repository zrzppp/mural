#include "../src/MuGlobals.h"
#include "../src/MuCore.h"

#include "../src/MuAppController.h"
#include "../src/MuTimer.h"

#include <cstdio>

// Create a controller class for testing
class GameController : public mural::MuAppController {
    public:
        GameController() {}
        void init() {
            // Timeout
            timers.scheduleMessage([] {
                printf("Action: timeout after %d ms\n", 100);
            }, 100, false);
            timers.scheduleMessage([] {
                printf("Action: timeout after %d ms\n", 200);
            }, 200, false);
            timers.scheduleMessage([] {
                printf("Action: timeout after %d ms\n", 300);
            }, 300, false);
            timers.scheduleMessage([] {
                printf("Action: timeout after %d ms\n", 400);
            }, 400, false);
            timers.scheduleMessage([] {
                printf("Action: timeout after %d ms\n", 500);
            }, 500, false);
            // Interval
            static int count = 0;
            int timeId = timers.scheduleMessage([&] {
                count++;
                printf("Action: interval repeat %d times\n", count);
            }, 80, true);
            // Clear interval
            timers.scheduleMessage([=] {
                timers.cancelMessage(timeId);
            }, 800, false);
        }
        void update(Number dt) {
            timers.update();
        }
    private:
        mural::MuTimerCollection timers;
};

int main(int argc, char const *argv[]) {
    // Initialize everything
    app.init();
    // Set a game controller which provides REAL logic
    app.setController(new GameController);
    // Start the game
    app.start();
    // Cleanup anything and quit
    app.terminate();

    return 0;
}
