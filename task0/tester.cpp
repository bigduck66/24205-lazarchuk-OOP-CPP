#include "tester.h"
#include "file_reader.h"
#include "text_processor.h"
#include "word_analyzer.h"
#include "csv_writer.h"
#include <iostream>
#include <fstream>
#include <cassert>

void Tester::testFileReader() {
    std::cout << "=== Тестирование FileReader ===" << std::endl;
    
    FileReader reader;
    
    // Тест 1: Чтение несуществующего файла
    bool result = reader.readFile("nonexistent.txt");
    assert(!result);
    std::cout << "Тест 1 пройден: Обработка несуществующего файла" << std::endl;
    
    // Тест 2: Создание тестового файла и чтение
    std::ofstream testFile("test_input.txt");
    testFile << "Hello world!\nThis is a test.";
    testFile.close();
    
    result = reader.readFile("test_input.txt");
    assert(result);
    assert(reader.getLineCount() == 2);
    std::cout << "Тест 2 пройден: Успешное чтение файла" << std::endl;
    
    std::cout << "Все тесты FileReader пройдены!\n" << std::endl;
}

void Tester::testTextProcessor() {
    std::cout << "=== Тестирование TextProcessor ===" << std::endl;
    
    // Тест 1: Приведение к нижнему регистру
    std::string result = TextProcessor::toLower("Hello WORLD");
    assert(result == "hello world");
    std::cout << "Тест 1 пройден: toLower" << std::endl;
    
    // Тест 2: Разбиение на слова
    std::vector<std::string> words = TextProcessor::splitIntoWords("Hello, world! This is-test.");
    assert(words.size() == 5);
    assert(words[0] == "Hello");
    assert(words[1] == "world");
    std::cout << "Тест 2 пройден: splitIntoWords" << std::endl;
    
    // Тест 3: Проверка символов
    assert(TextProcessor::isWordChar('a') == true);
    assert(TextProcessor::isWordChar('5') == true);
    assert(TextProcessor::isWordChar('!') == false);
    assert(TextProcessor::isWordChar(' ') == false);
    std::cout << "Тест 3 пройден: isWordChar" << std::endl;

    // Тест 4: Обработка нескольких строк
    std::list<std::string> testLines;
    testLines.push_back("Hello world!");
    testLines.push_back("This is a test.");
    std::vector<std::string> processedWords = TextProcessor::processLines(testLines);
    assert(processedWords.size() == 6);
    assert(processedWords[0] == "hello");
    assert(processedWords[1] == "world");
    assert(processedWords[2] == "this");
    assert(processedWords[3] == "is");
    assert(processedWords[4] == "a");
    assert(processedWords[5] == "test");
    std::cout << "Тест 4 пройден: processLines" << std::endl;
    
    std::cout << "Все тесты TextProcessor пройдены!\n" << std::endl;
}

void Tester::testWordAnalyzer() {
    std::cout << "=== Тестирование WordAnalyzer ===" << std::endl;
    
    WordAnalyzer analyzer;
    
    // Теперь передаем готовые слова, а не сырые строки
    std::vector<std::string> testWords;
    testWords.push_back("hello");
    testWords.push_back("world");
    testWords.push_back("hello");
    testWords.push_back("test");
    testWords.push_back("world");
    
    analyzer.analyzeWords(testWords);
    
    // Тест 1: Подсчет общего количества слов
    assert(analyzer.getTotalWords() == 5);
    std::cout << "Тест 1 пройден: Подсчет общего количества слов" << std::endl;
    
    // Тест 2: Подсчет уникальных слов
    assert(analyzer.getUniqueWordsCount() == 3);
    std::cout << "Тест 2 пройден: Подсчет уникальных слов" << std::endl;
    
    // Тест 3: Проверка частот
    auto frequency = analyzer.getWordFrequency();
    assert(frequency["hello"] == 2);
    assert(frequency["world"] == 2);
    assert(frequency["test"] == 1);
    std::cout << "Тест 3 пройден: Проверка частот слов" << std::endl;
    
    // Тест 4: Сортировка
    auto sorted = analyzer.getSortedWords();
    assert(sorted[0].first == "hello" || sorted[0].first == "world");
    assert(sorted[0].second == 2);
    std::cout << "Тест 4 пройден: Сортировка по частоте" << std::endl;
    
    std::cout << "Все тесты WordAnalyzer пройдены!\n" << std::endl;
}

void Tester::testCSVWriter() {
    std::cout << "=== Тестирование CSVWriter ===" << std::endl;
    
    std::vector<std::pair<std::string, int>> testData;
    testData.push_back(std::make_pair("hello", 3));
    testData.push_back(std::make_pair("world", 2));
    testData.push_back(std::make_pair("test", 1));
    
    // Тест 1: Запись в файл
    bool result = CSVWriter::writeCSV("test_output.csv", testData, 6);
    assert(result);
    std::cout << "Тест 1 пройден: Успешная запись в CSV" << std::endl;
    
    // Тест 2: Проверка содержимого файла
    std::ifstream checkFile("test_output.csv");
    std::string line;
    std::getline(checkFile, line); // Заголовок
    assert(line == "Слово,Частота,Частота (%)");
    std::cout << "Тест 2 пройден: Проверка заголовка CSV" << std::endl;
    
    checkFile.close();
    std::cout << "Все тесты CSVWriter пройдены!\n" << std::endl;
}

void Tester::runAllTests() {
    std::cout << "Запуск всех тестов...\n" << std::endl;
    
    testFileReader();
    testTextProcessor();
    testWordAnalyzer();
    testCSVWriter();
    
    std::cout << "Все тесты успешно пройдены!" << std::endl;
}