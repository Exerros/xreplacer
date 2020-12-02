#include "replacer.hpp"

namespace epx_test {

//Конструктор класса, при создании объекта "заменителя", сразу выполняет
//разбор пар для замены из файла, переданного в виде пути.
    Replacer::Replacer(const string& filePath)
        :maxSearchSize()
    {
        //Создаем все необходимые переменные. Инициализируем класс регулярных
        //выражений от первого выражения, которое ищет необходимый блок
        //информации. Буфер файла создается на основе переданного из функции
        // get_buf_and_close rvalue char* буфера.
        string fileBuf(move(get_buf_and_close(filePath)));
        regex reg(UPPER_REGULAR_STRING);
        smatch match;

        //Здесь происходит поиск необходимого блока информации для его
        //дальнейшего парсинга и подмена регулярного выражения для дальнейшего
        //поиска необходимой информации уже в этом блоке информации.
        regex_search(fileBuf, match, reg);
        reg = regex(LOWER_REGULAR_STRING);
        fileBuf = match[1].str();

        //В данном блоке происходит парсинг информации уже до вида пар "что" и
        //"на что" которые будут использоваться для замен.
        //Дополнительно в данном блоке происходит вычисление самой длинной
        //заменяемой строки и запоминаются все первые символы лексем. Это
        //позже будет использовано в функции fast_replace_in
        while(true == regex_search(fileBuf, match, reg)) {
            if(match[1].str().size() > maxSearchSize)
                maxSearchSize = match[1].str().length();

            searchSymbols.insert(match[1].str()[0]);
            pairs.insert(make_pair(move(match[1]), move(match[3])));
            fileBuf = match.suffix();
        }
    }

    //Данная функция лишь считывает буфер из файла и возвращает его функциям.
    char* Replacer::get_buf_and_close(const string& filePath) const {
        ifstream file(filePath);

        //Узнаем размер файла
        file.seekg(0, std::ios::end);
        long length = file.tellg();
        file.seekg(0, std::ios::beg);

        //Читаем буфер
        char* tmpBuf = new char[static_cast<unsigned long>(length)];
        file.read(tmpBuf, length);
        file.close();

        return tmpBuf;
    }

    //Данная функция как и fast_replace_in занимается заменой лексем в
    //переданных в виде пути файлах. В данной вариации функции применен более
    //медленный, но при том более легкочитаемый вариант кода.
    pair<uint32_t, string> Replacer::replace_in(const string& filePath) const {
        uint32_t replaceCount = 0;
        string fileBuf(move(get_buf_and_close(filePath)));

        //проверяем весь файл на наличие лексем. Контроль за заменами полностью
        //передан классу regex
        for(const auto& p : pairs) {
            regex reg(p.first);

            //.begin указывается дважды, потому что в первый раз он используется
            //как output_iterator, т.е. как итератор позиции записи измененного
            //значения
            regex_replace(
                fileBuf.begin(),
                fileBuf.begin(),
                fileBuf.end(),
                reg,
                p.second
            );
        }
        ofstream output_file(filePath);
        output_file << fileBuf;
        output_file.close();

        //Результатом работы не случайно выбрана пара из пути и числа замен
        //Это будет использовано для информирования пользователя
        return make_pair(replaceCount, move(filePath));
    }

    //Более быстрый и менее читаемый вариант replace_in
    //логика в целом та же, но для сокращения числа операций пришлось
    //использовать комбинацию из вложенных циклов.
    //В данной реализации минимизируется число операций:
    //буфер данных проверяется лишь один раз, но сразу на все лексемы, а если
    //точнее то проверяется наличие лексем начинающихся с проверяемого символа
    //после этого происходит попытка замены в подстроке размером с самую длинную
    //лексему. После этого происходит проверка замены и если замена была
    //произведена, то итератор i сдвигается на следующую позицию после лексемы
    //пропуская часть ненужных проверок.
    pair<uint32_t, string>
    Replacer::fast_replace_in(const string& filePath) const {
        uint32_t replaceCount = 0;
        string fileBuf(std::move(get_buf_and_close(filePath)));
        auto i = fileBuf.begin();

        //пока буфер не пуст
        while(i != fileBuf.end()) {
            //проверяем является ли символ началом лексемы
            for(const auto& ch : searchSymbols) {
                if(*i == ch) {
                    //пытаемся заменить
                    for(const auto& p : pairs) {
                        regex reg(p.first);
                        auto iTmp = regex_replace(
                            i,
                            i,
                            min(next(i, maxSearchSize), fileBuf.end()),
                            reg,
                            p.second);

                        //Если замена произошла засчитываем ее и производим
                        //сдвиг в ее конец
                        if(string(i,next(i, p.second.length())) == p.second) {
                            ++replaceCount;
                            i = prev(iTmp);//prev чтобы не перешагнуть за end
                            break;//выходим в цикл проверки символа
                        }
                    }
                    break; // выходим в while если символ подошел
                }
            }
            i = next(i);
        }

        ofstream output_file(filePath);
        output_file << fileBuf;
        output_file.close();

        return make_pair(replaceCount, move(filePath));
    }

    //Простая функция для отображения считанных из конфига пар.
    void Replacer::show_pairs() const {
        cout << "Pairs of replacements: \n";
        for(const auto& [key, value] : pairs) {
            cout << '\"' << key << "\" will be replaced to \""
                      << value << "\"\n";
        }
        flush(cout);
    }
}
