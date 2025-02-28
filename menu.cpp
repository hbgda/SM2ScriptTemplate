#include "menu.h"

#include "game/HeroSystem.h"
#include "game/Component/Health.h"

// It's best to use fully capitalised text for all your labels, 
// to better fit in with the games design style

float health_change = 0.0f;
void HealthMenu::Create() {
    Button("LOG HEALTH", nullptr, [](){
        DEBUG("Health: %p", GetHeroSystem()->GetHero()->GetComponent<Health>());
    });
    
    Button("KILL PLAYER", "Kill the player!", [](){
        Actor* hero = GetHeroSystem()->GetHero();
        if (!hero) {
            DEBUG("Failed to get hero!");
            return;
        }

        hero->GetComponent<Health>()->SetHealth(0);
    });

    Button("HEAL PLAYER", "Heal the player to full health!", [](){
        Actor* hero = GetHeroSystem()->GetHero();
        if (!hero) {
            DEBUG("Failed to get hero!");
            return;
        }
        auto health = hero->GetComponent<Health>();
        health->SetHealth(health->GetMaxHealth());
    });

    Header("CHANGE HEALTH");

    float max_health = GetHeroSystem()->GetHero()->GetComponent<Health>()->GetMaxHealth();
    SliderOpts health_opts;
    health_opts.max = max_health;
    health_opts.display_max = (int)max_health;
    Slider("HEALTH AMOUNT", nullptr, &health_change, health_opts);
    Button("ADD HEALTH", "Add the chosen amount of health!", [](){
        Actor* hero = GetHeroSystem()->GetHero();
        if (!hero) {
            DEBUG("Failed to get hero!");
            return;
        }
        auto health = hero->GetComponent<Health>();
        health->SetHealth(health->GetHealth() + health_change);
    });

    Button("REMOVE HEALTH", "Remove the chosen amount of health!", [](){
        Actor* hero = GetHeroSystem()->GetHero();
        if (!hero) {
            DEBUG("Failed to get hero!");
            return;
        }
        auto health = hero->GetComponent<Health>();
        health->SetHealth(health->GetHealth() - health_change);
    });
}