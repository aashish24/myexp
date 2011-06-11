
#ifndef __TOKEN_STREAM_H__
#define __TOKEN_STREAM_H__

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
