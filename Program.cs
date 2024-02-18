using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace LT_Lab1
{

    internal class Program
    {

        class Entry
        {

            public Entry(string? text = null, int wordCount = 0)
            {
                Text = text;
                this.wordCount = wordCount;
            }

            public string? Text { get; set; }
            public int wordCount { get; set; }

            public override string ToString()
            {
                return Text + $"\t[words: {wordCount}]";
            }

        }

        static bool isWord(string? word)
        {
            return word != null ? word.Any(x => char.IsLetter(x)) : false;
        }

        static string? removeDelimeters(string? word)
        {

            if (word == null)
            {
                return null;
            }

            for (int i = 0; i < word.Length; ++i)
            {
                if (char.IsLetter(word[i]) || char.IsDigit(word[i]) || word[i] == '\'' || word[i] == '-')
                {
                    continue;
                }
                else
                {
                    word = word.Remove(i);
                }
            }

            return word;

        }

        static bool compareLetters(string? word1, string? word2)
        {

            if (word1 == null || word2 == null)
            {
                return false;
            }

            if (word1.Length == 0 && word2.Length == 0) 
            {
                return true;
            }
            else if (word1.Length == 0 || word2.Length == 0)
            {
                return false;
            }

            if (word1.ToLower().First() == word2.ToLower().Last())
            {
                return true;
            }
            else
            {
                return false;
            }

        }



        static void Main(string[] args)
        {


            HashSet<string> set = new HashSet<string>();
            set.Add("a");

            set.Add("b");

            set.Add("c");

            set.Add("a");

            foreach (var item in set)
            {
                Console.WriteLine(item);
            }

            Console.ReadLine();
            string path = "file_in.txt";
            string filename = "file_out.txt";

            StreamReader? reader = null;
            StreamWriter? writer = null;

            try 
            {
                reader = File.OpenText(path);
                writer = File.CreateText(filename);
            }
            catch(FileNotFoundException? ex) 
            {
                Console.WriteLine(ex.Message);
                reader?.Close();
                writer?.Close();
                return;
            }



            int[] delimeters = { '.', '!', '?' };
            StringBuilder sentence = new StringBuilder();
            int character;

            int totalSentenceCount = 0;
            List<Entry> entries = new List<Entry>();



            while (!reader.EndOfStream)
            {

                character = reader.Read();

                if (sentence.Length == 0 && character == ' ')
                {
                    continue;
                }

                sentence.Append((char)character);

                if (delimeters.Contains(character))
                {

                    string[] words = sentence.ToString().Split(' ');

                    if (compareLetters(removeDelimeters(words.FirstOrDefault(isWord)), removeDelimeters(words.LastOrDefault(isWord))))
                    {
                        entries.Add(new Entry(sentence.ToString(), words.Where(isWord).Count()));
                    }

                    ++totalSentenceCount;

                    sentence.Clear();

                }

            }

            reader.Close();



            Console.WriteLine($"Total sentences found: {totalSentenceCount}");
            writer.WriteLine($"Total sentences found: {totalSentenceCount}");
            if (entries.Count != 0)
            {
                foreach (var entry in entries)
                {
                    Console.WriteLine(entry);
                    writer.WriteLine(entry);
                }
            }
            else 
            { 
                Console.WriteLine("No entries satisfying the condition were found.");
                writer.WriteLine("No entries satisfying the condition were found.");
            }
            
            writer.Close();

        }

    }

}