<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0">

<xsl:template match="/">
  <html>
  <body>
  <xsl:apply-templates/>
  </body>
  </html>
</xsl:template>

<xsl:template match="titre">
<h3>Titre: <span style="color:#ff0000">
<xsl:value-of select="."/></span></h3>
</xsl:template>

<xsl:template match="prenom">
<xsl:value-of select="."/>
</xsl:template>

<xsl:template match="nom">
<span style="color:#ff0000">
<xsl:value-of select="."/></span>
<br/>
</xsl:template>

<xsl:template match="auteur">
  <span>Auteur: </span>
</xsl:template>

<xsl:template match="resume">
<span>Resume: </span>
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="p">
  <xsl:value-of select="."/>
  <br />
</xsl:template>

</xsl:stylesheet>
