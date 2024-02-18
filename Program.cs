using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


namespace MyProject
{
    class Program
    {

        static int found_vowels(string word, List<char> vowels)
        { 
            int count_vowels = 0;

            foreach (char ch in word)
            {
                if(Char.IsLetter(ch))
                { 
                    if(vowels.Contains(ch))
                    {
                        count_vowels++;
                    }
                }
            }

            return count_vowels;
        }

        static void Main(string[] args)
        {
            string path_r = @"D:\Study\Курс 2.2\MovTex\M_Lab1\M_Lab1\file_in.txt";
            string path_w = @"D:\Study\Курс 2.2\MovTex\M_Lab1\M_Lab1\file_out.txt";


            List<char> vowels = new List<char> { 'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', 'Y', 'y' };
            string? text = "";
            HashSet<string> two_vowels = new HashSet<string>();


            using (StreamReader sr = new StreamReader(path_r, Encoding.Default)) 
            { 
                while((text = sr.ReadLine())!=null)
                {
                    string[] words = text.Split(new char[] { ' ', ',', ':', '.', ';', '!', '?', '(', ')', '"' }, StringSplitOptions.RemoveEmptyEntries);
                    foreach (string word in words)
                    {
                        if(found_vowels(word, vowels) == 2)
                        {
                            two_vowels.Add(word);
                        }
                    }
                }
            }



            Console.Write("Всього двоскладових слiв: ");

            Console.WriteLine($"{two_vowels.Count()}\n");

            foreach (string word in two_vowels)
            {
                Console.WriteLine(word);
            }
            Console.WriteLine("----------------------------------------------\n\n");



            using (StreamWriter wr = new StreamWriter(path_w, true)) 
            {
                wr.Write("Всього двоскладових слiв: ");

                wr.WriteLine($"{two_vowels.Count()}\n");

                foreach (string word in two_vowels)
                { wr.WriteLine(word); }
                wr.WriteLine("----------------------------------------------\n\n");
            }
        }
    }
}
