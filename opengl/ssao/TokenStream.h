/*
   Token Stream
   Game Graphics Programming
   Created by Allen Sherrod

   Purpose:
      For reading words from a buffer one at a time using delimiters.
*/


#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_


class TokenStream
{
   public:
      TokenStream();
      ~TokenStream();

      void ResetStream();

      void SetTokenStream(char *data);
      bool GetNextToken(std::string *buffer);
      bool GetNextToken(std::string *token, std::string *buffer);

      bool MoveToNextLine(std::string *buffer);

   private:
      int m_startIndex, m_endIndex;
      std::string m_data;
};

#endif