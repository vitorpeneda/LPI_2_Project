using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.IO;
using System.Windows.Forms;



namespace PortaSerie
{

    static class Constants                 //Classe que permite definir as constantes (semelhante ao #define da linguagem C).
    {
        public const int DIM_BUFFER_RX = 25;                //Tamanho do buffer de recepção.  
        public const int DIM_Data_Hora = 25;
        public const char CARACTER_INICIO_TRAMA = '$';      //Caractér sinalizador do início de trama.
        public const char CARACTER_FIM_TRAMA = '\r';        //Caractér sinalizador do fim de trama.
    }


    public class Metodos_Porta_Serie        //Classe que permite aceder à porta série enviando ou recebendo tramas.
    {
        SerialPort PORTA_SERIE = new SerialPort();                              //Atributo interno da porta série.
        int Index_RX;						                                    //Índice do buffer de recepção.
        int Reception_RX;					                                    //Controlo da recepção dos bytes.
        int[] Buffer_RX = new int[Constants.DIM_BUFFER_RX];                     //Buffer de recepção.
        int[] Data_Hora = new int[Constants.DIM_Data_Hora];
        int i;
        int j;
        int Temperatura;
        int aux;
        string trama = "";


        public bool Inicializar_Porta(string COM_Number, int COM_Baudrate)                              //Método que inicializa uma porta série. Retorna true se abrir correctamente ou false se ocorrer qualquer erro.
        {
            bool Ok = true;                                                                             //Variável auxiliar.
            if (PORTA_SERIE.IsOpen == true)                                                             //Verificar se a porta já está a ser usada (eventualmente por outra aplicação...).
            {
                return false;                                                                           //A porta já estava aberta. Verifique o problema e tente abrir novamente.
            }
            else
            {
                Index_RX = 0;                                                                           //Inicialização das variáveis de controlo.
                Reception_RX = 0;
                Temperatura = 0;
                i = 1;
                j = 0;
                aux = 0;
                PORTA_SERIE.PortName = COM_Number;                                                      //Definir número da porta série.
                PORTA_SERIE.BaudRate = COM_Baudrate;                                                    //Definir baudrate.
                PORTA_SERIE.DtrEnable = false;                                                          //Não usar o sinal DTR na comunicação.
                PORTA_SERIE.RtsEnable = false;                                                          //Não usar o sinal RTS na comunicação.
                PORTA_SERIE.ReadBufferSize = 4096;                                                      //Buffer de recepção com tamanho para 4096 bytes.
                PORTA_SERIE.WriteBufferSize = 4096;                                                     //Buffer de transmissão com tamanho para 4096 bytes.
                PORTA_SERIE.ReadTimeout = 500;                                                          //Timeout de 500ms para a recepção.
                PORTA_SERIE.WriteTimeout = 500;                                                         //Timeout de 500ms para a transmissão.
                PORTA_SERIE.ReceivedBytesThreshold = 1;                                                 //Sempre que receber 1 byte ocorre o evento DataReceived.
                PORTA_SERIE.DiscardNull = false;                                                        //Trata-se de transmissão binária, todos os bytes interessam.
                PORTA_SERIE.Parity = Parity.None;                                                       //Sem paridade.
                PORTA_SERIE.DataBits = 8;                                                               //8 bits de dados.
                PORTA_SERIE.StopBits = StopBits.One;                                                    //1 stop bit.
                PORTA_SERIE.Handshake = Handshake.None;                                                 //Handshake desligado.
                PORTA_SERIE.Encoding = Encoding.ASCII;                                                  //Usar tabela ascii.
                PORTA_SERIE.DataReceived += new SerialDataReceivedEventHandler(Evento_Recepcao);        //Anexar o evento de recepção de bytes.
                try
                {
                    PORTA_SERIE.Open();                                                                 //Tentar abrir a porta.
                    PORTA_SERIE.DiscardInBuffer();                                                      //Apagar buffer de recepção.
                    PORTA_SERIE.DiscardOutBuffer();                                                     //Apagar buffer de transmissão.
                }
                catch
                {
                    Ok = false;                                                                         //Erro. Não foi possível abrir a porta.
                }
                if (Ok == true)
                {
                    return true;                                                                        //Inicialização concluída com sucesso! Porta aberta e pronta a ser usada.
                }
                else
                {
                    PORTA_SERIE.DataReceived -= new SerialDataReceivedEventHandler(Evento_Recepcao);    //Como ocorreu um erro, desanexar o evento de recepção de bytes.
                    return false;                                                                       //Ocorreu um erro na inicialização! Verifique o problema e tente abrir novamente.
                }
            }
        }

        public void Fechar_Porta()                                                  //Método que fecha a porta série anteriormente aberta.
        {
            PORTA_SERIE.DataReceived -= new SerialDataReceivedEventHandler(Evento_Recepcao);        //Desanexar o evento de recepção de bytes.
            PORTA_SERIE.Close();                                                                    //Fechar definitivamente a porta série.
        }

        private bool IsFileLocked(string trama)
        {
            try
            {
                File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
            }
            catch (IOException)
            {
                IsFileLocked(trama);
                //textBox9.Text = "File is in use";
                //the file is unavailable because it is:
                //still being written to
                //or being processed by another thread
                //or does not exist (has already been processed)
                return true;
            }

            //file is not locked
            return false;
        }

        private void Escreve_ficheiro(string trama)
        {

            IsFileLocked(trama);


        }

        private void Processar_Comando()
        {

            if (Buffer_RX[0] == 'D')//dados relativos a data
            {
                trama = "\n D:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + (Buffer_RX[4] - 48) + "-" + (Buffer_RX[6] - 48) +
                    (Buffer_RX[7] - 48) + "-" + (Buffer_RX[9] - 48) + (Buffer_RX[10] - 48);
                //System.Console.WriteLine(trama);
                Escreve_ficheiro(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
            }
            if (Buffer_RX[0] == 'C')//dados relativos a hora
            {
                trama = " C:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + ":" + (Buffer_RX[4] - 48) + (Buffer_RX[5] - 48)
                              + ":" + (Buffer_RX[7] - 48) + (Buffer_RX[8] - 48);
                //System.Console.WriteLine(trama);
                Escreve_ficheiro(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
            }
            else if (Buffer_RX[0] == 'S')//dados relativos a windSpeed
            {
                trama = " S:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + "." + (Buffer_RX[5] - 48) + (Buffer_RX[6] - 48);
                // System.Console.WriteLine(trama);
                Escreve_ficheiro(trama);

                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
            }
            else if (Buffer_RX[0] == 'W')//dados relativos a windDirection
            {
                trama = " W:" + retorna_letra(Buffer_RX[1]) + retorna_letra(Buffer_RX[2]);
                // System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);

            }
            else if (Buffer_RX[0] == 'A')//dados relativos a windDirection
            {
                trama = " A:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48);
                // System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);

            }
            else if (Buffer_RX[0] == 'R')//dados relativos a Rainfall
            {
                trama = " R:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + "." + (Buffer_RX[5] - 48) + (Buffer_RX[6] - 48);
                // System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);

            }
            else if (Buffer_RX[0] == 'H')//dados relativos a Humidade
            {
                trama = " H:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + "." + (Buffer_RX[5] - 48) + (Buffer_RX[6] - 48);
                // System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);

            }
            else if (Buffer_RX[0] == 'T')//dados relativos a Temperatura
            {
                if (Buffer_RX[1] == 43)
                {
                    trama = " T:+" + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + (Buffer_RX[4] - 48) + "." + (Buffer_RX[6] - 48) + (Buffer_RX[7] - 48);
                }
                else if (Buffer_RX[1] == 45)
                {
                    trama = " T:-" + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + (Buffer_RX[4] - 48) + "." + (Buffer_RX[6] - 48) + (Buffer_RX[7] - 48);
                }
                //System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);

            }
            else if (Buffer_RX[0] == 'P')//dados relativos a Pressao
            {
                trama = " P:" + (Buffer_RX[1] - 48) + (Buffer_RX[2] - 48) + (Buffer_RX[3] - 48) + (Buffer_RX[4] - 48) + "."
                    + (Buffer_RX[6] - 48) + (Buffer_RX[7] - 48);
                //System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", "\n");
            }
            else if (Buffer_RX[0] == 'B')//dados relativos a Bateria
            {
                trama = " B:" + (Buffer_RX[1] - 48);
                //System.Console.WriteLine(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", trama);
                Escreve_ficheiro(trama);
                //System.IO.File.AppendAllText(@"C:\Users\Vitor\Documents\My Dropbox\LPI_Project\WS_data.txt", "\n");
            }
        }

        char retorna_letra(int valor)
        {
            char letra = ' ';
            if (valor == 69)
            {
                letra = 'E';
            }
            else if (valor == 78)
            {
                letra = 'N';
            }
            else if (valor == 83)
            {
                letra = 'S';
            }
            else if (valor == 87)
            {
                letra = 'W';
            }
            return letra;
        }



        private void Evento_Recepcao(object sender, SerialDataReceivedEventArgs e)  //Evento desplotado pela recepção de um byte.
        {
            int Byte_Lido = 0;                                          //Variável auxiliar.
            do
            {
                Byte_Lido = PORTA_SERIE.ReadByte();					    //Ler byte proveniente da porta série.
                if (Byte_Lido == Constants.CARACTER_INICIO_TRAMA)	    //Detectar start condition (Caracter de start).
                {
                    Index_RX = 0;									    //Inicializar variáveis de controlo. 
                    Reception_RX = 1;								    //A trama vai começar a ser guardada.
                }
                else if (Reception_RX == 1)
                {
                    if (Index_RX == Constants.DIM_BUFFER_RX)	        //O limite do buffer foi atingido. Está completamente preenchido.
                    {
                        if (Byte_Lido == Constants.CARACTER_FIM_TRAMA)
                        {
                            Processar_Comando();                        //O último caracter era o terminador. Por isso ignorar overflow do buffer e processar.
                        }
                        Reception_RX = 0;							    //Re-inicializar a variável de controlo.
                    }
                    else
                    {
                        if (Byte_Lido != Constants.CARACTER_FIM_TRAMA)  //Verificar se o caracter finalizador já chegou.
                        {
                            Buffer_RX[Index_RX] = Byte_Lido;		    //Guardar no buffer o byte recebido. O caractér terminador ainda não chegou.
                            Index_RX++;
                        }
                        else
                        {
                            Processar_Comando();                        //Processar comando. O caractér terminador já chegou.
                            Reception_RX = 0;						    //Re-inicializar a variável de controlo.
                        }
                    }
                }
            } while (PORTA_SERIE.BytesToRead != 0);                     //Executar ciclo enquanto os bytes no buffer não tiverem sido todos lidos.
        }
    }
}
