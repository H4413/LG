<?xml version="1.0" encoding="UTF-8" ?>

<xsl:stylesheet version="1.0">

  <xsl:template match="persons">
    <html>
      <head> <title>Testing XML Example</title> </head>
      <body>
        <h1>Persons</h1>
        <ul>
          <xsl:apply-templates/>
        </ul>
      </body>
    </html>
  </xsl:template>
 
  <xsl:template match="person">
    <li>
      <xsl:value-of/>
    </li>
  </xsl:template>
 
</xsl:stylesheet>
