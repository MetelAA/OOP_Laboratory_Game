//
// Created by Artem on 20.11.2025.
//

#include "Renderer.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <cstdlib>

void Renderer::prepareConsole() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(1251);
}

void Renderer::draw() {
    std::vector<std::vector<std::string>> chars(this->field.getHeight(), std::vector<std::string>(this->field.getWidth(), " "));
    for (int x = 0; x < this->field.getHeight(); ++x) {
        for (int y = 0; y < this->field.getWidth(); ++y) {
            if(this->field.getFieldCells()[x][y].getCellType() == CellType::Impassable){
                chars[x][y] = Renderer::WALL;
            }else if (this->field.getFieldCells()[x][y].hasEntityInCell()){
                chars[x][y] = this->entityTypeToCharS.at(this->field.getFieldCells()[x][y].getEntityInCellType());
            }else if(this->field.getFieldCells()[x][y].hasCellEvent()){
                chars[x][y] = this->cellEventTypeToCharS.at(this->field.getFieldCells()[x][y].getCellEventType());
            }
        }
    }
    chars[this->field.getHeight()-1][this->field.getWidth()-1] = EXIT;
    drawGridRounded(chars);
    displayEntitiesInfo();
    displayLegend();
}

void Renderer::drawGridRounded(const std::vector<std::vector<std::string>> &grid) {
    if (grid.empty()) return;

    int height = this->field.getHeight();
    int width = this->field.getWidth();

    std::cout << "╭";
    for (int x = 0; x < width; ++x) {
        std::cout << "───";
        if (x < width - 1) std::cout << "┬";
    }
    std::cout << "╮" << std::endl;

    for (int y = 0; y < height; ++y) {
        std::cout << "│";
        for (int x = 0; x < width; ++x) {
            std::cout << " " << grid[y][x] << " ";
            if (x < width - 1) std::cout << "│";
        }
        std::cout << "│" << std::endl;

        if (y < height - 1) {
            std::cout << "├";
            for (int x = 0; x < width; ++x) {
                std::cout << "───";
                if (x < width - 1) std::cout << "┼";
            }
            std::cout << "┤" << std::endl;
        }
    }

    std::cout << "╰";
    for (int x = 0; x < width; ++x) {
        std::cout << "───";
        if (x < width - 1) std::cout << "┴";
    }
    std::cout << "╯" << std::endl;
}

void Renderer::displayLegend() {
    std::cout << "┌─────────────────────────────┐" << std::endl;
    std::cout << "│          Легенда            │" << std::endl;
    std::cout << "├─────────────┬───────────────┤" << std::endl;
    std::cout << "│ " << "◎" << " - Игрок   │ " << "●" << " - Враг      │" << std::endl;
    std::cout << "│ " << "■" << " - Стена   │ " << "▲" << " - Башня     │" << std::endl;
    std::cout << "│ " << "♦" << " - Спавнер │ " << "A" << " - Союзник   │" << std::endl;
    std::cout << "│ " << "→" << " - Выход   │ " << "×" << " - Ловушка   │" << std::endl;
    std::cout << "└─────────────┴───────────────┘" << std::endl;
}

void Renderer::displayEntitiesInfo() {
    if (entities.empty()) {
        std::cout << "No entities." << std::endl;
        return;
    }

    std::cout << "┌────────Сущности─────────┐" << std::endl;

    std::cout << "│" << std::setw(3) << std::right << "№  " << "│"
              << std::setw(10) << std::left << "Type" << "│"
              << std::setw(5) << std::left << "x/y" << "│"
              << std::setw(4) << std::right << "HP" << "│" << std::endl;

    std::cout << "├───┼──────────┼─────┼────┤" << std::endl;

    for (size_t i = 0; i < entities.size(); ++i) {
        const auto& entity = entities[i];
        EntityType type = entity->getType();
        std::string typeStr = "Unknown";

        auto it = entityTypeToStr.find(type);
        if (it != entityTypeToStr.end()) {
            typeStr = it->second;
        }


        int x = entity->getXCoordinate();
        int y = entity->getYCoordinate();
        int hp = entity->getHealthPoints();

        std::string posStr = std::to_string(y+1) + "/" + std::to_string(x+1);
        if (posStr.length() > 5) {
            posStr = posStr.substr(0, 5);
        }

        std::cout << "│" << std::setw(3) << std::right << (i+1) << "│"
                  << std::setw(10) << std::left << typeStr << "│"
                  << std::setw(5) << std::left << posStr << "│"
                  << std::setw(4) << std::right << hp << "│" << std::endl;
    }
    std::cout << "└───┴──────────┴─────┴────┘" << std::endl;
}

void Renderer::clearDisplay() {
    system("cls");
}
