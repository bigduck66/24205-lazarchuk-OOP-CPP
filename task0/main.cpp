#include <iostream>
#include "file_reader.h"
#include "text_processor.h"
#include "word_analyzer.h"
#include "csv_writer.h"
#include "tester.h"

int main(int argc, char* argv[]) {
    // Если передан аргумент --test, запускаем тесты
    if (argc == 2 && std::string(argv[1]) == "--test") {
        Tester::runAllTests();
        return 0;
    }
    
    // Обычный режим работы
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " input.txt output.csv" << std::endl;
        std::cerr << "Или для тестов: " << argv[0] << " --test" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Создаем объекты классов
    FileReader fileReader;
    WordAnalyzer wordAnalyzer;

    // Читаем файл
    if (!fileReader.readFile(inputFile)) {
        return 1;
    }

    // TextProcessor полностью подготавливает данные
    std::vector<std::string> processedWords = 
        TextProcessor::processLines(fileReader.getLines());

    // WordAnalyzer только анализирует готовые слова
    wordAnalyzer.analyzeWords(processedWords);

    // Записываем результат
    if (!CSVWriter::writeCSV(outputFile, 
                           wordAnalyzer.getSortedWords(),
                           wordAnalyzer.getTotalWords())) {
        return 1;
    }

    std::cout << "Программа завершена успешно!" << std::endl;
    std::cout << "Итоговая статистика:" << std::endl;
    std::cout << "- Всего слов: " << wordAnalyzer.getTotalWords() << std::endl;
    std::cout << "- Уникальных слов: " << wordAnalyzer.getUniqueWordsCount() << std::endl;

    return 0;
}