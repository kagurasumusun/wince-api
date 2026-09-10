/*
 * Msxml2.h -- Microsoft XML Core Services (MSXML) types, constants
 * and COM interface records for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Applications and Services Development > XML book, 501 leaves
 * harvested under tools/manifests/msxml.manifest, M66).
 *
 * The Requirements rows print "Header: Msxml2.h, Msxml2.idl" and
 * "Link Library: Uuid.lib" -- the file name msxml2.h is the compat
 * surface (Win32 software includes <msxml2.h>).  The CE MSXML is a
 * C++ COM API: no page publishes a vtable layout, so -- following the
 * M44 objbase.h interface-record policy -- each interface is carried
 * as an opaque forward declaration plus verbatim method/accessor
 * signature records.  The Uuid.lib rows sit on interface/method/
 * property pages (GUID linkage, not import-library export symbols),
 * so no import-library def is derived from this book.
 *
 * The book's scripting-level surfaces (XPath/XQL functions, XSLT
 * elements, msxsl:script) are not C API and are catalogued in
 * docs/inventory.md only.  The error-message pages (IXMLParseError /
 * XML DOM / XQL / XSLT Error Messages) print message text tables,
 * not error constants -- no defines are derivable (catalogued).
 */

#ifndef AKARI_MSXML2_H
#define AKARI_MSXML2_H

#include "Windef.h"
#include "Objbase.h"   /* VARIANT, BSTR, VARIANT_BOOL, IDispatch,
                          IStream carriers (M44) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* ms897200 "XML DOM Enumerated Constants" -- DOMNodeType (Windows CE   */
/* .NET 4.0 and later; Msxml2.h, Msxml2.idl).  Verbatim enum print:     */
/*   enum tagDOMNodeType {NODE_INVALID,NODE_ELEMENT, 1                  */
/*     NODE_ATTRIBUTE,NODE_TEXT,NODE_CDATA_SECTION,                     */
/*     NODE_ENTITY_REFERENCE,NODE_ENTITY,                               */
/*     NODE_PROCESSING_INSTRUCTION,NODE_COMMENT,NODE_DOCUMENT,         */
/*     NODE_DOCUMENT_TYPE,NODE_DOCUMENT_FRAGMENT,                       */
/*     NODE_NOTATION} DOMNodeType;                                      */
/* Values: the element descriptions print NODE_ELEMENT (1) through      */
/* NODE_NOTATION (12) explicitly; NODE_INVALID is the zeroth element    */
/* and has no description -- 0 by position (recorded sequential         */
/* reading).                                                            */
/* ------------------------------------------------------------------ */
typedef enum tagDOMNodeType {
    NODE_INVALID                = 0,
    NODE_ELEMENT                = 1,
    NODE_ATTRIBUTE              = 2,
    NODE_TEXT                   = 3,
    NODE_CDATA_SECTION          = 4,
    NODE_ENTITY_REFERENCE       = 5,
    NODE_ENTITY                 = 6,
    NODE_PROCESSING_INSTRUCTION = 7,
    NODE_COMMENT                = 8,
    NODE_DOCUMENT               = 9,
    NODE_DOCUMENT_TYPE          = 10,
    NODE_DOCUMENT_FRAGMENT      = 11,
    NODE_NOTATION               = 12
} DOMNodeType;

/* ------------------------------------------------------------------ */
/* MSXML interfaces (XML DOM Objects/Interfaces aa513829 lists 21 DOM   */
/* interfaces + XMLSchemaCache/IXMLDOMSchemaCollection +               */
/* IXMLDOMSelection; XML HTTP aa513838 lists IXMLHTTPRequest; XML SAX  */
/* aa513852 and the XML Minimal Parser ms897202 list the ISAX_ and */
/* IMX_ set; aa513878 lists IXTLRuntime).  Opaque forward declarations */
/* set; aa513878 lists IXTLRuntime).  Opaque forward declarations      */
/* (M44 policy: the docs publish method signatures, never vtable       */
/* layouts).                                                            */
/* ------------------------------------------------------------------ */
typedef struct IXMLDOMAttribute         IXMLDOMAttribute;
typedef struct IXMLDOMCDATASection      IXMLDOMCDATASection;
typedef struct IXMLDOMCharacterData     IXMLDOMCharacterData;
typedef struct IXMLDOMComment           IXMLDOMComment;
typedef struct IXMLDOMDocument2         IXMLDOMDocument2;
typedef struct IXMLDOMDocumentFragment  IXMLDOMDocumentFragment;
typedef struct IXMLDOMDocumentType      IXMLDOMDocumentType;
typedef struct IXMLDOMElement           IXMLDOMElement;
typedef struct IXMLDOMEntity            IXMLDOMEntity;
typedef struct IXMLDOMEntityReference   IXMLDOMEntityReference;
typedef struct IXMLDOMImplementation    IXMLDOMImplementation;
typedef struct IXMLDOMNamedNodeMap      IXMLDOMNamedNodeMap;
typedef struct IXMLDOMNode              IXMLDOMNode;
typedef struct IXMLDOMNodeList          IXMLDOMNodeList;
typedef struct IXMLDOMNotation          IXMLDOMNotation;
typedef struct IXMLDOMParseError        IXMLDOMParseError;
typedef struct IXMLDOMProcessingInstruction IXMLDOMProcessingInstruction;
typedef struct IXMLDOMSelection         IXMLDOMSelection;
typedef struct IXMLDOMText              IXMLDOMText;
typedef struct IXMLHTTPRequest          IXMLHTTPRequest;
typedef struct IXTLRuntime              IXTLRuntime;
typedef struct IXMLDOMSchemaCollection  IXMLDOMSchemaCollection;
typedef struct ISAXAttributes           ISAXAttributes;
typedef struct ISAXContentHandler       ISAXContentHandler;
typedef struct ISAXDTDHandler           ISAXDTDHandler;
typedef struct ISAXDeclHandler          ISAXDeclHandler;
typedef struct ISAXEntityResolver       ISAXEntityResolver;
typedef struct ISAXErrorHandler         ISAXErrorHandler;
typedef struct ISAXLexicalHandler       ISAXLexicalHandler;
typedef struct ISAXLocator              ISAXLocator;
typedef struct ISAXXMLFilter            ISAXXMLFilter;
typedef struct ISAXXMLReader            ISAXXMLReader;
typedef struct IMXAttributes            IMXAttributes;
typedef struct IMXReaderControl         IMXReaderControl;
typedef struct IMXWriter                IMXWriter;

/* Auxiliary names recorded (no CE 5.0 page of their own):
 * DOMDocument (ms864435) -- the document coclass, created with the
 *   progID "Msxml2.DOMDocument" (ms892577 print; the CLSID value is
 *   not published).
 * XMLSchemaCache/IXMLDOMSchemaCollection (ms897206) -- the book title
 *   names both spellings; the XMLSchemaCache coclass page itself is
 *   absent from the CE 5.0 book.
 * IXMLDOMDocument (base of IXMLDOMDocument2 on desktop MSXML) -- no
 *   CE 5.0 page carries it; it appears nowhere in the CE book titles.
 * IXMLDSOControl -- absent from the CE 5.0 book (desktop-only).
 * ISAXXMLReader30 / SAXXMLReader30 / SAXXMLReader coclass spellings
 *   -- the CE pages print "ISAXXMLReader:IUnknown Interface" (See
 *   Also form, ms885896) and ms897202 states the XML Minimal Parser
 *   "provides two co-classes that implement the XML Reader interface"
 *   without naming them.
 * IID_/CLSID_ GUIDs -- not published anywhere in the book (the
 *   Uuid.lib Link Library rows imply GUID linkage, values held).
 * VARIANT input forms of ISAXXMLReader::parse (VT_BSTR, SafeArray of
 *   bytes, VT_UNK(IStream)/(ISequentialStream), one-level VT_BYREF
 *   referencing) are printed on ms885896 remarks.
 *
 * XML DOM Events (aa513822): ondataavailable (ms892606) and
 * onreadystatechange (ms892608) print "HRESULT onXxx( void );" C/C++
 * event signatures; ontransformnode (ms892611) prints no C/C++
 * section (script-only page; the event sink names are catalogued).
 * The property pages carry the sink wiring: put_onreadystatechange
 * (DOMDocument ms892609 VARIANT; IXMLHTTPRequest ms892610
 * Idispatch* -- the doc's casing print).
 */

/* ------------------------------------------------------------------ */
/* Verbatim method/accessor signature records (243 pages with C/C++     */
/* prints; archive type-space traps preserved inside the recorded      */
/* lines).  Alphabetical by title within each section; the title       */
/* carries the printed interface qualifier.                            */
/* ------------------------------------------------------------------ */

/* XML DOM shared method/property pages (153 pages; Windows CE .NET 4.0 and
 *      later; Msxml2.h, Msxml2.idl; Link Library: Uuid.lib). DOM
 *      methods/properties are shared across the node interfaces; the title
 *      carries the interface qualifier where the book prints one.
 *      Signatures are verbatim C/C++ Syntax prints; archive type-space
 *      traps preserved (BSTRbstrNodeName, VARIANTvarDate)
 *   aa513894 abort Method: HRESULT abort( );
 *   aa513897 abort Method (DOMDocument): HRESULT abort( void );
 *   aa513912 add Method: HRESULT add(BSTR namespaceURI,VARIANT var);
 *   aa513906 addAttribute Method: HRESULT
 *      addAttribute(BSTRstrURI,BSTRstrLocalName,BSTRstrQName,BSTRstrType,B
 *      STRstrValue);
 *   aa513904 addAttributeFromIndex Method: HRESULT
 *      addAttributeFromIndex(VARIANTvarAtts,intnIndex);
 *   aa513908 addCollection Method: HRESULT
 *      addCollection(IXMLDOMSchemaCollection* otherCollection);
 *   ms863652 appendChild Method: HRESULT appendChild(IXMLDOMNode*
 *      newChild,IXMLDOMNode** outNewChild);
 *   ms863662 appendData Method: HRESULT appendData(BSTRdata);
 *   ms863678 async Property: HRESULT get_async(VARIANT_BOOL* isAsync);
 *   ms863678 async Property: HRESULT put_async(VARIANT_BOOLisAsync);
 *   ms863687 attributes Property: HRESULT
 *      get_attributes(IXMLDOMNamedNodeMap** attributeMap);
 *   ms863702 baseName Property: HRESULT get_baseName(BSTR* nameString);
 *   ms863870 byteOrderMark Property: HRESULT byteOrderMark([in]
 *      VARIANT_BOOLfWriteByteOrderMark);
 *   ms863870 byteOrderMark Property: [propget]HRESULTbyteOrderMark([out,
 *      retval] VARIANT_BOOL* fWriteByteOrderMark);
 *   ms863875 childNodes Property: HRESULT get_childNodes(IXMLDOMNodeList**
 *      childList);
 *   ms863878 clear Method: HRESULT clear();
 *   ms863880 clone Method: HRESULT clone(IXMLDOMSelection** ppNode);
 *   ms863881 cloneNode Method: HRESULT
 *      cloneNode(VARIANT_BOOLdeep,IXMLDOMNode** cloneRoot);
 *   ms864013 context Property: HRESULT get_context(IXMLDOMNode** ppNode);
 *   ms864013 context Property: HRESULT putref_context(IXMLDOMNode* pNode);
 *   ms864384 createAttribute Method: HRESULT
 *      createAttribute(BSTRname,IXMLDOMAttribute** attribute);
 *   ms864386 createCDATASection Method: HRESULT
 *      createCDATASection(BSTRdata,IXMLDOMCDATASection** cdata);
 *   ms864388 createComment Method: HRESULT
 *      createComment(BSTRdata,IXMLDOMComment** comment);
 *   ms864389 createDocumentFragment Method: HRESULT
 *      createDocumentFragment(IXMLDOMDocumentFragment** docFrag);
 *   ms864390 createElement Method: HRESULT
 *      createElement(BSTRtagName,IXMLDOMElement** element);
 *   ms864391 createEntityReference Method: HRESULT
 *      createEntityReference(BSTRname,IXMLDOMEntityReference** entityRef);
 *   ms864396 createNode Method: HRESULT
 *      createNode(VARIANTType,BSTRname,BSTRnamespaceURI,IXMLDOMNode**
 *      node);
 *   ms864400 createProcessingInstruction Method: HRESULT
 *      createProcessingInstruction(BSTRtarget,BSTRdata,IXMLDOMProcessingIn
 *      struction** pi);
 *   ms864402 createTextNode Method: HRESULT
 *      createTextNode(BSTRdata,IXMLDOMText** text);
 *   ms864409 data Property (IXMLDOMCharacterData): HRESULT get_data(BSTR*
 *      data);
 *   ms864409 data Property (IXMLDOMCharacterData): HRESULT
 *      put_data(BSTRdata);
 *   ms864410 data Property (IXMLDOMProcessingInstruction): HRESULT
 *      get_data(BSTR* value);
 *   ms864410 data Property (IXMLDOMProcessingInstruction): HRESULT
 *      put_data(BSTRvalue);
 *   ms864411 dataType Property: HRESULT get_dataType(VARIANT*
 *      dataTypeName);
 *   ms864411 dataType Property: HRESULT put_dataType(BSTRdataTypeName);
 *   ms864412 definition Property: HRESULT get_definition(IXMLDOMNode**
 *      definitionNode);
 *   ms864413 deleteData Method: HRESULT deleteData(longoffset,longcount);
 *   ms864420 disableOutputEscaping Property:
 *      [propput]HRESULTdisableOutputEscaping([in] VARIANT_BOOLfValue);
 *   ms864420 disableOutputEscaping Property: [propget]HRESULT
 *      disableOutputEscaping([out, retval] VARIANT_BOOL* fValue);
 *   ms864431 doctype Property: HRESULT get_doctype(IXMLDOMDocumentType**
 *      documentType);
 *   ms864433 documentElement Property: HRESULT
 *      get_documentElement(IXMLDOMElement** DOMElement);
 *   ms864433 documentElement Property: HRESULT
 *      putref_documentElement(IXMLDOMElement* DOMElement);
 *   ms864459 encoding Property: [propput]HRESULTencoding([in]
 *      BSTRstrEncoding);
 *   ms864459 encoding Property: [propget]HRESULTencoding([out, retval]
 *      BSTR* strEncoding);
 *   ms864463 entities Property: HRESULT get_entities(IXMLDOMNamedNodeMap**
 *      entityMap);
 *   aa514721 errorCode Property: HRESULT get_errorCode(long* errorCode);
 *   aa514949 expr Property: HRESULT get_expr(BSTR* expression);
 *   aa514949 expr Property: HRESULT put_expr(BSTR expression);
 *   aa514979 filepos Property: HRESULT get_filepos(long* filePosition);
 *   aa514984 firstChild Property: HRESULT get_firstChild(IXMLDOMNode**
 *      firstChild);
 *   aa514989 flush Method: HRESULT flush( );
 *   aa515045 get Method: HRESULT get(BSTR namespaceURI,IXMLDOMNode**
 *      schemaNode);
 *   aa515017 getAttribute Method: HRESULT getAttribute(BSTRname,VARIANT*
 *      value);
 *   aa515020 getAttributeNode Method: HRESULT
 *      getAttributeNode(BSTRname,IXMLDOMAttribute** attributeNode);
 *   aa515033 getElementsByTagName Method (DOMDocument): HRESULT
 *      getElementsByTagName(BSTRtagName,IXMLDOMNodeList** resultList);
 *   aa515035 getElementsByTagName Method (IXMLDOMElement): HRESULT
 *      getElementsByTagName(BSTRtagName,IXMLDOMNodeList** resultList);
 *   aa515046 getNamedItem Method: HRESULT
 *      getNamedItem(BSTRname,IXMLDOMNode** namedItem);
 *   aa515051 getProperty Method (IXMLDOMDocument2): HRESULT
 *      getProperty(BSTRname,VARIANT* value);
 *   aa515053 getProperty Method (IXMLDOMSelection): HRESULT
 *      getProperty(BSTRname,VARIANT* value);
 *   aa515055 getQualifiedItem Method: HRESULT
 *      getQualifiedItem(BSTRbaseName,BSTRnamespaceURI,IXMLDOMNode**qualifi
 *      edItem);
 *   aa515075 hasChildNodes Method: HRESULT hasChildNodes(VARIANT_BOOL*
 *      hasChild);
 *   aa515077 hasFeature Method: HRESULT
 *      hasFeature(BSTRfeature,BSTRversion,VARIANT_BOOL* hasFeature);
 *   ms882815 implementation Property: HRESULT
 *      get_implementation(IXMLDOMImplementation** impl);
 *   ms882858 indent Property: [propput]HRESULTindent([in]
 *      VARIANT_BOOLfIndentMode);
 *   ms882858 indent Property: [propget]HRESULTindent([out, retval]
 *      VARIANT_BOOL* fIndentMode);
 *   ms882873 input Property: HRESULT get_input(VARIANT* pVar);
 *   ms882873 input Property: HRESULT put_input(VARIANT pVar);
 *   ms882875 insertBefore Method: HRESULT insertBefore(IXMLDOMNode*
 *      newChild,VARIANTrefChild,IXMLDOMNode** outNewChild);
 *   ms882876 insertData Method: HRESULT insertData(longoffset,BSTRdata);
 *   ms890859 item Method (IXMLDOMNamedNodeMap): HRESULT
 *      item(longindex,IXMLDOMNode** listItem);
 *   ms890866 item Method (IXMLDOMNodeList): HRESULT
 *      item(longindex,IXMLDOMNode** listItem);
 *   ms891739 lastChild Property: HRESULT get_lastChild(IXMLDOMNode**
 *      lastChild);
 *   ms892323 length Property (IXMLDOMCharacterData): HRESULT
 *      get_length(long* dataLength);
 *   ms892324 length Property (IXMLDOMNamedNodeMap): HRESULT length(long*
 *      listLength);
 *   ms892325 length Property (IXMLDOMNodeList): HRESULT get_length(long*
 *      listLength);
 *   ms892326 length Property (XMLSchemaCache/IXMLSchemaCollection):
 *      HRESULT length(long* length);
 *   ms892329 line Property: HRESULT get_line(long* lineNumber);
 *   ms892328 linepos Property: HRESULT get_linepos(long* linePosition);
 *   ms892330 load Method: HRESULT load(VARIANTxmlSource,VARIANT_BOOL*
 *      isSuccessful);
 *   ms892337 loadXML Method: HRESULT loadXML(BSTRbstrXML,VARIANT_BOOL*
 *      isSuccessful);
 *   ms892343 matches Method: HRESULT matches(IXMLDOMNode*
 *      pNode,IXMLDOMNode** ppNode);
 *   ms892357 name Property (IXMLDOMAttribute): HRESULT get_name(BSTR*
 *      attributeName);
 *   ms892358 name Property (IXMLDOMDocumentType): HRESULT get_name(BSTR*
 *      rootName);
 *   ms892406 namespaces Property: HRESULT
 *      get_namespaces(IXMLDOMSchemaCollection** namespaceCollection);
 *   ms892429 namespaceURI Property (IXMLDOMNode): HRESULT
 *      get_namespaceURI(BSTR* namespaceURI);
 *   ms892438 namespaceURI Property (XMLSchemaCache/IXMLSchemaCollection):
 *      HRESULT get_namespaceURI(long index,BSTR* length);
 *   ms892452 nextNode Method (IXMLDOMNamedNodeMap): HRESULT
 *      nextNode(IXMLDOMNode** nextItem);
 *   ms892462 nextNode Method (IXMLDOMNodeList): HRESULT
 *      nextNode(IXMLDOMNode** nextItem);
 *   ms892468 nextSibling Property: HRESULT get_nextSibling(IXMLDOMNode**
 *      nextSibling);
 *   ms892563 nodeFromID Method: HRESULT
 *      nodeFromID(BSTRidString,IXMLDOMNode** node);
 *   ms892572 nodeName Property: HRESULT get_nodeName(BSTR* name);
 *   ms892577 nodeType Property: HRESULT get_nodeType(DOMNodeType* type);
 *   ms892576 nodeTypedValue Property: HRESULT get_nodeTypedValue(VARIANT*
 *      typedValue);
 *   ms892576 nodeTypedValue Property: HRESULT put_nodeTypedValue(VARIANT
 *      typedValue);
 *   ms892578 nodeTypeString Property: HRESULT get_nodeTypeString(BSTR*
 *      nodeType);
 *   ms892579 nodeValue Property: HRESULT get_nodeValue(VARIANT* value);
 *   ms892579 nodeValue Property: HRESULT get_nodeValue(VARIANT value);
 *   ms892580 normalize Method: HRESULT normalize(void);
 *   ms892582 notationName Property: HRESULT get_notationName(BSTR* name);
 *   ms892583 notations Property: HRESULT
 *      get_notations(IXMLDOMNamedNodeMap** notationMap);
 *   ms892605 omitXMLDeclaration Property: [propput]HRESULT
 *      omitXMLDeclaration([in] VARIANT_BOOLfValue);
 *   ms892605 omitXMLDeclaration Property: [propget]HRESULT
 *      omitXMLDeclaration([out, retval] VARIANT_BOOL* fValue);
 *   ms892607 ondataavailable Property: HRESULT put_ondataavailable(VARIANT
 *      ondataavailableSink);
 *   ms892609 onreadystatechange Property (DOMDocument): HRESULT
 *      put_onreadystatechange(VARIANT readystatechangeSink);
 *   ms892612 ontransformnode Property: HRESULT put_ontransformnode(VARIANT
 *      ontransformnodeSink);
 *   ms892615 output Property: HRESULT get_output(VARIANT* pOutput);
 *   ms892615 output Property: HRESULT put_output(VARIANT output);
 *   ms892618 ownerDocument Property: HRESULT
 *      get_ownerDocument(IXMLDOMDocument** DOMDocument);
 *   ms892621 parentNode Property: HRESULT get_parentNode(IXMLDOMNode**
 *      parent);
 *   ms892622 parsed Property: HRESULT get_parsed(VARIANT_BOOL* isParsed);
 *   ms892623 parseError Property: HRESULT
 *      get_parseError(IXMLDOMParseError** errorObj);
 *   ms892627 peekNode Method: HRESULT peekNode (IXMLDOMNode** ppNode);
 *   ms892631 prefix Property: HRESULT get_prefix(BSTR* prefixString);
 *   ms892632 preserveWhiteSpace Property: HRESULT
 *      get_preserveWhiteSpace(VARIANT_BOOL* isPreserving);
 *   ms892632 preserveWhiteSpace Property: HRESULT
 *      put_preserveWhiteSpace(VARIANT_BOOL isPreserving);
 *   ms892633 previousSibling Property: HRESULT
 *      get_previousSibling(IXMLDOMNode** previousSibling);
 *   ms892637 publicId Property (IXMLDOMEntity): HRESULT get_publicId(BSTR*
 *      publicID);
 *   ms892638 publicId Property (IXMLDOMNotation): HRESULT
 *      get_publicId(VARIANT* publicID);
 *   ms892645 readyState Property (DOMDocument): HRESULT
 *      get_readyState(long* value);
 *   ms892647 reason Property: HRESULT get_reason(BSTR* reasonString);
 *   ms892655 remove Method: HRESULT remove(BSTRnamespaceURI);
 *   ms892650 removeAll Method: HRESULT removeAll();
 *   ms892651 removeAttribute Method: HRESULT removeAttribute(BSTRname);
 *   ms892653 removeAttributeNode Method: HRESULT
 *      removeAttributeNode(IXMLDOMAttribute*
 *      DOMAttribute,IXMLDOMAttribute** attributeNode);
 *   ms892654 removeChild Method: HRESULT removeChild(IXMLDOMNode*
 *      childNode,IXMLDOMNode** outOldChild);
 *   ms892656 removeNamedItem Method: HRESULT
 *      removeNamedItem(BSTRname,IXMLDOMNode** namedItem);
 *   ms892657 removeNext Method: HRESULT removeNext(IXMLDOMNode** ppNode);
 *   ms892658 removeQualifiedItem Method: HRESULT
 *      removeQualifiedItem(BSTRbaseName,BSTRnamespaceURI,IXMLDOMNode**
 *      qualifiedItem);
 *   ms892659 replaceChild Method: HRESULT replaceChild(IXMLDOMNode*
 *      newChild,IXMLDOMNode* oldChild,IXMLDOMNode** outOldChild);
 *   ms892660 replaceData Method: HRESULT
 *      replaceData(longoffset,longcount,BSTRdata);
 *   ms893262 reset Method (IXMLDOMNamedNodeMap): HRESULT reset( void );
 *   ms893268 reset Method (IXMLDOMNodeList): HRESULT reset( void );
 *   ms893273 resolveExternals Property: HRESULT
 *      get_resolveExternals(VARIANT_BOOL* isResolving);
 *   ms893273 resolveExternals Property: HRESULT
 *      put_resolveExternals(VARIANT_BOOLisResolving);
 *   ms893304 resume Method: HRESULT resume( );
 *   ms893443 save Method: HRESULT save(VARIANTdestination);
 *   ms893448 schemas Property: HRESULT get_schemas(VARIANT*
 *      otherCollection);
 *   ms893448 schemas Property: HRESULT
 *      putref_schemas(VARIANTotherCollection);
 *   ms893450 selectNodes Method: HRESULT
 *      selectNodes(BSTRexpression,IXMLDOMNodeList** resultList);
 *   ms893451 selectSingleNode Method: HRESULT
 *      selectSingleNode(BSTRqueryString,IXMLDOMNode** resultNode);
 *   ms893454 setAttribute Method: HRESULT
 *      setAttribute(BSTRname,VARIANTvalue);
 *   ms893456 setAttributeNode Method: HRESULT
 *      setAttributeNode(IXMLDOMAttribute* DOMAttribute,IXMLDOMAttribute**
 *      attributeNode);
 *   ms893457 setAttributes Method: HRESULT setAttributes(IMXAttributes*
 *      varAtts);
 *   ms893459 setLocalName Method: HRESULT
 *      setLocalName(intnIndex,BSTRstrLocalName);
 *   ms893460 setNamedItem Method: HRESULT setNamedItem(IXMLDOMNode*
 *      newItem,IXMLDOMNode** nameItem);
 *   ms893462 setProperty Method: HRESULT
 *      setProperty(BSTRname,VARIANTvalue);
 *   ms893464 setQName Method: HRESULT setQName(intnIndex,BSTRstrQName);
 *   ms893466 setStartMode Method: HRESULT
 *      setStartMode(BSTRmode,BSTRnamespaceURI);
 *   ms893467 setType Method: HRESULT setType(intnIndex,BSTRstrType);
 *   ms893468 setURI Method: HRESULT setURI(intnIndex,BSTRstrURI);
 *   ms893469 setValue Method: HRESULT setValue(intnIndex,BSTRstrValue);
 *   ms895354 specified Property: HRESULT get_specified(VARIANT_BOOL*
 *      isSpecified);
 *   ms895592 splitText Method: HRESULT splitText(longoffset,IXMLDOMText**
 *      rightHandTextNode);
 *   ms895975 srcText Property: HRESULT get_srcText(BSTR* sourceString);
 *   ms895976 standalone Property: [propput]HRESULT standalone([in]
 *      VARIANT_BOOLfValue );
 *   ms895976 standalone Property: [propget]HRESULT standalone([out,
 *      retval] VARIANT_BOOL* fValue);
 *   ms896450 substringData Method: HRESULT
 *      substringData(longoffset,longcount,BSTR* data);
 *   ms896469 suspend Method: HRESULT suspend( );
 *   ms896479 systemId Property (IXMLDOMEntity): HRESULT
 *      get_systemId(VARIANT* systemID);
 *   ms896480 systemId Property (IXMLDOMNotation): HRESULT
 *      get_systemId(VARIANT* systemID);
 *   ms896483 tagName Property: HRESULT get_tagName(BSTR* tagName);
 *   ms896484 target Property: HRESULT get_target(BSTR* name);
 *   ms896485 text Property: HRESULT get_text(BSTR* text);
 *   ms896487 transformNode Method: HRESULT transformNode(IXMLDOMNode*
 *      stylesheet,BSTR* xmlString);
 *   ms896488 transformNodeToObject Method: HRESULT
 *      transformNodeToObject(IXMLDOMNode* stylesheet,VARIANToutputObject);
 *   ms896497 uniqueID Method: HRESULT uniqueID(IXMLDOMNode* pNode,long*
 *      pID);
 *   ms896501 url Property (DOMDocument): HRESULT get_url(BSTR* urlString);
 *   ms896502 url Property (IXMLDOMParseError): HRESULT get_url(BSTR*
 *      urlString);
 *   ms896503 validate Method: HRESULT validate(IXMLDOMParseError**
 *      errorObj);
 *   ms896504 validateOnParse Property: HRESULT
 *      get_validateOnParse(VARIANT_BOOL* isValidating);
 *   ms896504 validateOnParse Property: HRESULT
 *      put_validateOnParse(VARIANT_BOOLisValidating);
 *   ms896505 value Property: HRESULT get_value(VARIANT* attributeValue);
 *   ms896505 value Property: HRESULT put_value(VARIANT* attributeValue);
 *   ms897185 version Property: [propput]HRESULT version([in]
 *      BSTRstrVersion);
 *   ms897185 version Property: [propget]HRESULT version([out, retval]
 *      BSTR* strVersion);
 *   ms897205 xml Property: HRESULT get_xml(BSTR* xmlString);
 */

/* XSLT (IXTLRuntime) methods (8 pages)
 *   aa513902 absoluteChildNumber Method: HRESULT
 *      absoluteChildNumber(IXMLDOMNode* pNode,long* pNumber);
 *   ms863540 ancestorChildNumber Method: HRESULT
 *      ancestorChildNumber(BSTRbstrNodeName,IXMLDOMNode *pNode,long
 *      *pNumber);
 *   ms863876 childNumber Method: HRESULT childNumber(IXMLDOMNode*
 *      pNode,long* pNumber);
 *   ms864414 depth Method: HRESULT depth(IXMLDOMNode* pNode,long* pDepth);
 *   aa514991 formatDate Method: HRESULT
 *      formatDate(VARIANTvarDate,BSTRbstrFormat,VARIANTvarDestLocale,BSTR*
 *      pbstrFormattedString);
 *   aa514995 formatIndex Method: HRESULT
 *      formatIndex(longlIndex,BSTRbstrFormat,BSTR* pbstrFormattedString);
 *   aa514997 formatNumber Method: HRESULT
 *      formatNumber(doubledblNumber,BSTRbstrFormat,BSTR*
 *      pbstrFormattedString);
 *   aa515001 formatTime Method: HRESULT
 *      formatTime(VARIANTvarTime,BSTRbstrFormat,VARIANTvarDestLocale,BSTR*
 *      pbstrFormattedString);
 */

/* XML HTTP (IXMLHTTPRequest) methods/properties (14 pages)
 *   aa513899 abort Method (IXMLHTTPRequest): HRESULT abort(void);
 *   aa515016 getAllResponseHeaders Method (IXMLHTTPRequest): HRESULT
 *      getAllResponseHeaders(BSTR* pbstrHeaders);
 *   aa515058 getResponseHeader Method (IXMLHTTPRequest): HRESULT
 *      getResponseHeader(BSTRbstrHeader, BSTR* pbstrValue);
 *   ms892610 onreadystatechange Property (IXMLHTTPRequest): HRESULT
 *      put_onreadystatechange(Idispatch* pReadyStateSink);
 *   ms892613 open Method (IXMLHTTPRequest): HRESULT
 *      open(BSTRbstrMethod,BSTRbstrUrl,VARIANTvarAsync,VARIANTbstrUser,VAR
 *      IANTbstrPassword);
 *   ms892646 readyState Property (IXMLHTTPRequest): HRESULT
 *      get_readyState(long* plState);
 *   ms893279 responseBody Property (IXMLHTTPRequest): HRESULT
 *      get_responseBody(VARIANT* pvarBody);
 *   ms893286 responseStream Property (IXMLHTTPRequest): HRESULT
 *      get_responseStream(VARIANT* pvarBody);
 *   ms893295 responseText Property (IXMLHTTPRequest): HRESULT
 *      get_responseText(BSTR* pbstrBody);
 *   ms893299 responseXML Property (IXMLHTTPRequest): HRESULT
 *      get_responseXML(Idispatch** ppBody);
 *   ms893452 send Method (IXMLHTTPRequest): HRESULT send(VARIANTvarBody);
 *   ms893465 setRequestHeader Method (IXMLHTTPRequest): HRESULT
 *      setRequestHeader(BSTRbstrHeader,BSTRbstrValue);
 *   ms896205 status Property (IXMLHTTPRequest): HRESULT get_status(long*
 *      plStatus);
 *   ms896213 statusText Property (IXMLHTTPRequest): HRESULT
 *      get_statusText(BSTR* pbstrStatus);
 */

/* XML SAX interfaces: methods/properties by interface. */

/* IMXAttributes / IMXWriter (unqualified SAX pages): 3 documented pages
 *   ms892616 output Property (XML SAX): [propput]HRESULT output([in]
 *      VARIANTvarDestination);
 *   ms892616 output Property (XML SAX): [propget]HRESULT output([out,
 *      retval] VARIANT* varDestination);
 *   ms892652 removeAttribute Method (XML SAX): HRESULT
 *      removeAttribute(intnIndex);
 *   ms893455 setAttribute Method (XML SAX): HRESULT
 *      setAttribute(intnIndex,BSTRstrURI,BSTRstrLocalName,BSTRstrQName,BST
 *      RstrType,BSTRstrValue);
 */

/* ISAXAttributes: 13 documented pages
 *   ms884605 ISAXAttributes::getIndexFromName Method: HRESULT
 *      getIndexFromName(const wchar_t* pwchUri,intcchUri,const wchar_t*
 *      pwchLocalName,intcchLocalName,int* pnIndex);
 *   ms884606 ISAXAttributes::getIndexFromQName Method: HRESULT
 *      getIndexFromQName(const wchar_t* pwchQName,intcchQName, int*
 *      pnIndex);
 *   ms884607 ISAXAttributes::getLength Method: HRESULT getLength(int*
 *      pnLength);
 *   ms884608 ISAXAttributes::getLocalName Method: HRESULT
 *      getLocalName(intnIndex,const wchar_t** ppwchLocalName,int*
 *      pcchLocalName);
 *   ms884609 ISAXAttributes::getName Method: HRESULT
 *      getName(intnIndex,const wchar_t** ppwchUri,int* pcchUri,const
 *      wchar_t** ppwchLocalName,int* pcchLocalName,const wchar_t**
 *      ppwchQName,int* pcchQName);
 *   ms884610 ISAXAttributes::getQName Method: HRESULT
 *      getQName(intnIndex,const wchar_t** ppwchQName,int* ppchQName);
 *   ms884613 ISAXAttributes::getType Method: HRESULT
 *      getType(intnIndex,const wchar_t** ppwchType,int* pcchType);
 *   ms884611 ISAXAttributes::getTypeFromName Method: HRESULT
 *      getTypeFromName(const wchar_t* pwchUri,intcchUri,const wchar_t*
 *      pwchLocalName,intcchLocalName,const wchar_t** ppwchType,int*
 *      pcchType);
 *   ms884612 ISAXAttributes::getTypeFromQName Method: HRESULT
 *      getTypeFromQName(const wchar_t* pwchQName,intcchQName,const
 *      wchar_t** ppwchType,int* pcchType);
 *   ms884614 ISAXAttributes::getURI Method: HRESULT getURI(intnIndex,
 *      const wchar_t** ppwchUri, int* pcchUri);
 *   ms884617 ISAXAttributes::getValue Method: HRESULT
 *      getValue(intnIndex,const wchar_t** ppwchValue,int* pcchValue);
 *   ms884615 ISAXAttributes::getValueFromName Method: HRESULT
 *      getValueFromName(const wchar_t* pwchUri,intcchUri,const wchar_t*
 *      pwchLocalName,intcchLocalName,const wchar_t** ppwchValue,int*
 *      pcchValue);
 *   ms884616 ISAXAttributes::getValueFromQName Method: HRESULT
 *      getValueFromQName(const wchar_t* pwchQName,intcchQName,const
 *      wchar_t** pwchValue,int* pcchValue);
 */

/* ISAXContentHandler: 11 documented pages
 *   ms884619 ISAXContentHandler::characters Method: HRESULT
 *      characters(const wchar_t* pwchChars,intcchChars);
 *   ms885122 ISAXContentHandler::endDocument Method: HRESULT endDocument();
 *   ms885225 ISAXContentHandler::endElement Method: HRESULT
 *      endElement(const wchar_t* pwchNamespaceUri,intcchNamespaceUri,const
 *      wchar_t* pwchLocalName,intcchLocalName,const wchar_t*
 *      pwchQName,intcchQName);
 *   ms885233 ISAXContentHandler::endPrefixMapping Method: HRESULT
 *      endPrefixMapping(const wchar_t* pwchPrefix,intcchPrefix);
 *   ms885241 ISAXContentHandler::ignorableWhitespace Method: HRESULT
 *      ignorableWhitespace(const wchar_t* pwchChars,intcchChars);
 *   ms885252 ISAXContentHandler::processingInstruction Method: HRESULT
 *      processingInstruction(const wchar_t* pwchTarget,intcchTarget,const
 *      wchar_t* pwchData,intcchData);
 *   ms885259 ISAXContentHandler::putDocumentLocator Method: HRESULT
 *      putDocumentLocator(ISAXLocator* pLocator);
 *   ms885268 ISAXContentHandler::skippedEntity Method: HRESULT
 *      skippedEntity(const wchar_t* pwchName,int cchName );
 *   ms885277 ISAXContentHandler::startDocument Method: HRESULT
 *      startDocument();
 *   ms885287 ISAXContentHandler::startElement Method: HRESULT
 *      startElement(const wchar_t*
 *      pwchNamespaceUri,intcchNamespaceUri,const wchar_t*
 *      pwchLocalName,intcchLocalName,const wchar_t*
 *      pwchQName,intcchQName,ISAXAttributes* pAttributes);
 *   ms885291 ISAXContentHandler::startPrefixMapping Method: HRESULT
 *      startPrefixMapping(const wchar_t* pwchPrefix,int cchPrefix,const
 *      wchar_t* pwchUri,intcchUri);
 */

/* ISAXDTDHandler: 2 documented pages
 *   ms885329 ISAXDTDHandler::notationDecl Method: HRESULT
 *      notationDecl(const wchar_t* pwchName,intcchName,const wchar_t*
 *      pwchPublicId,intcchPublicId,const wchar_t*
 *      pwchSystemId,intcchSystemId);
 *   ms885338 ISAXDTDHandler::unparsedEntityDecl Method: HRESULT
 *      unparsedEntityDecl(const wchar_t* pwchName,intcchName,const
 *      wchar_t* pwchPublicId,intcchPublicId,const wchar_t*
 *      pwchSystemId,intcchSystemId,const wchar_t*
 *      pwchNotationName,intcchNotationName);
 */

/* ISAXDeclHandler: 4 documented pages
 *   ms885297 ISAXDeclHandler::attributeDecl Method: HRESULT
 *      attributeDecl(const wchar_t*
 *      pwchElementName,intcchElementName,const wchar_t*
 *      pwchAttributeName,intcchAttributeName,const wchar_t*
 *      pwchType,intcchType,const wchar_t*
 *      pwchValueDefault,intcchValueDefault,const wchar_t*
 *      pwchValue,intcchValue);
 *   ms885302 ISAXDeclHandler::elementDecl Method: HRESULT
 *      elementDecl(const wchar_t* pwchName,intcchName,const wchar_t*
 *      pwchModel,intcchModel);
 *   ms885304 ISAXDeclHandler::externalEntityDecl Method: HRESULT
 *      externalEntityDecl(const wchar_t* pwchName,intcchName,const
 *      wchar_t* pwchPublicId,intcchPublicId,const
 *      wchar_tpwchSystemId,intcchSystemId);
 *   ms885310 ISAXDeclHandler::internalEntityDecl Method: HRESULT
 *      internalEntityDecl(const wchar_t* pwchName,intcchName,const
 *      wchar_t* pwchValue,intcchValue);
 */

/* ISAXEntityResolver: 1 documented pages
 *   ms885348 ISAXEntityResolver::resolveEntity Method: HRESULT
 *      resolveEntity(const wchar_t* pwchPublicId,const wchar_t*
 *      pwchSystemId,VARIANT* pvarInput);
 */

/* ISAXErrorHandler: 3 documented pages
 *   ms885356 ISAXErrorHandler::error Method: HRESULT error(ISAXLocator*
 *      pLocator,const wchar_t* pwchErrorMessage,HRESULThrErrorCode);
 *   ms885365 ISAXErrorHandler::fatalError Method: HRESULT
 *      fatalError(ISAXLocator* pLocator,const wchar_t*
 *      pwchErrorMessage,HRESULThrErrorCode);
 *   ms885371 ISAXErrorHandler::ignorableWarning Method: HRESULT
 *      ignorableWarning(ISAXLocator* pLocator,const wchar_t*
 *      pwchErrorMessage,HRESULThrErrorCode);
 */

/* ISAXLexicalHandler: 7 documented pages
 *   ms885384 ISAXLexicalHandler::comment Method: HRESULT comment(const
 *      wchar_t* pwchChars,intcchChars);
 *   ms885393 ISAXLexicalHandler::endCDATA Method: HRESULT endCDATA();
 *   ms885400 ISAXLexicalHandler::endDTD Method: HRESULT endDTD();
 *   ms885408 ISAXLexicalHandler::endEntity Method: HRESULT EndEntity(const
 *      wchar_t* pwchName,intcchName);
 *   ms885428 ISAXLexicalHandler::startCDATA Method: HRESULT startCDATA();
 *   ms885437 ISAXLexicalHandler::startDTD Method: HRESULT startDTD( const
 *      wchar_t* pwchName, int cchName, const wchar_t* pwchPublicId, int
 *      cchPublicId, const wchar_t* pwchSystemId, int cchSystemId);
 *   ms885446 ISAXLexicalHandler::startEntity Method: HRESULT
 *      startEntity(const wchar_t* pwchName,intcchName);
 */

/* ISAXLocator: 4 documented pages
 *   ms885459 ISAXLocator::getColumnNumber Method: HRESULT
 *      getColumnNumber(int* pnColumn);
 *   ms885463 ISAXLocator::getLineNumber Method: HRESULT getLineNumber(int*
 *      pnLine);
 *   ms885470 ISAXLocator::getPublicId Method: HRESULT getPublicId(const
 *      wchar_t** ppwchPublicId);
 *   ms885479 ISAXLocator::getSystemId Method: HRESULT getSystemId(const
 *      wchar_t** ppwchSystemId);
 */

/* ISAXXMLFilter: 2 documented pages
 *   ms885492 ISAXXMLFilter::getParent Method: HRESULT
 *      getParent(ISAXXMLReader** ppReader);
 *   ms885506 ISAXXMLFilter::putParent Method: HRESULT
 *      putParent(ISAXXMLReader* pReader);
 */

/* ISAXXMLReader: 18 documented pages
 *   ms885514 ISAXXMLReader::getBaseURL Method: HRESULT getBaseURL(const
 *      wchar_t** ppwchBaseUrl);
 *   ms885592 ISAXXMLReader::getContentHandler Method: HRESULT
 *      getContentHandler(ISAXContentHandler** ppHandler);
 *   ms885696 ISAXXMLReader::getDTDHandler Method: HRESULT
 *      getDTDHandler(ISAXDTDHandler** ppHandler);
 *   ms885764 ISAXXMLReader::getEntityResolver Method: HRESULT
 *      getEntityResolver(ISAXEntityResolver** ppResolver);
 *   ms885832 ISAXXMLReader::getErrorHandler Method: HRESULT
 *      getErrorHandler(ISAXErrorHandler** ppHandler);
 *   ms885845 ISAXXMLReader::getFeature Method: HRESULT getFeature(const
 *      wchar_t* pwchName,VARIANT_BOOL* pvfValue);
 *   ms885855 ISAXXMLReader::getProperty Method: HRESULT getProperty(const
 *      wchar_t* pwchName,VARIANT* pvarValue);
 *   ms885868 ISAXXMLReader::getSecureBaseURL Method: HRESULT
 *      getSecureBaseURL(const wchar_t** ppwchSecureBaseUrl);
 *   ms885896 ISAXXMLReader::parse Method: HRESULT parse(VARIANTvarInput);
 *   ms885909 ISAXXMLReader::parseURL Method: HRESULT ParseURL(const
 *      wchar_t* pwchUrl);
 *   ms885922 ISAXXMLReader::putBaseURL Method: HRESULT putBaseURL(const
 *      wchar_t* pwchBaseUrl);
 *   ms885928 ISAXXMLReader::putContentHandler Method: HRESULT
 *      putContentHandler(ISAXContentHandler* pHandler);
 *   ms885941 ISAXXMLReader::putDTDHandler Method: HRESULT
 *      putDTDHandler(ISAXDTDHandler* pHandler);
 *   ms885950 ISAXXMLReader::putEntityResolver Method: HRESULT
 *      putEntityResolver(ISAXEntityResolver* pResolver);
 *   ms885961 ISAXXMLReader::putErrorHandler Method: HRESULT
 *      putErrorHandler(ISAXErrorHandler* pHandler);
 *   ms885972 ISAXXMLReader::putFeature Method: HRESULT putFeature(const
 *      wchar_t* pwchName,VARIANT_BOOL* vfValue);
 *   ms885985 ISAXXMLReader::putProperty Method: HRESULT putProperty(const
 *      wchar_t* pwchName,VARIANT* varValue);
 *   ms886006 ISAXXMLReader::putSecureBaseURL Method: HRESULT
 *      putSecureBaseURL (const wchar_t* pwchSecureBaseUrl);
 */

/* ------------------------------------------------------------------
 * Book surface: msxml (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa513894 abort Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa513897 abort Method (DOMDocument) (Header: Msxml2.) */
/* aa513899 abort Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* aa513902 absoluteChildNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa513912 add Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa513906 addAttribute Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa513904 addAttributeFromIndex Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa513908 addCollection Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863540 ancestorChildNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863652 appendChild Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863662 appendData Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863678 async Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms863687 attributes Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms863702 baseName Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms863870 byteOrderMark Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms863875 childNodes Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms863876 childNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863878 clear Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863880 clone Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms863881 cloneNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864013 context Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864384 createAttribute Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864386 createCDATASection Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864388 createComment Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864389 createDocumentFragment Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864390 createElement Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864391 createEntityReference Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864396 createNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864400 createProcessingInstruction Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864402 createTextNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864409 data Property (IXMLDOMCharacterData) (Header: Msxml2.h, Msxml2.idl.) */
/* ms864410 data Property (IXMLDOMProcessingInstruction) (Header: Msxml2.h, Msxml2.idl.) */
/* ms864411 dataType Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864412 definition Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864413 deleteData Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864414 depth Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms864420 disableOutputEscaping Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864431 doctype Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864433 documentElement Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864459 encoding Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms864463 entities Property (Header: Msxml2.h, Msxml2.idl.) */
/* aa514721 errorCode Property (Header: Msxml2.h, Msxml2.idl.) */
/* aa514949 expr Property (Header: Msxml2.h, Msxml2.idl.) */
/* aa514979 filepos Property (Header: Msxml2.h, Msxml2.idl.) */
/* aa514984 firstChild Property (Header: Msxml2.h, Msxml2.idl.) */
/* aa514989 flush Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa514991 formatDate Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa514995 formatIndex Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa514997 formatNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515001 formatTime Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515045 get Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515016 getAllResponseHeaders Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515017 getAttribute Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515020 getAttributeNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515033 getElementsByTagName Method (DOMDocument) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515035 getElementsByTagName Method (IXMLDOMElement) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515046 getNamedItem Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515051 getProperty Method (IXMLDOMDocument2) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515053 getProperty Method (IXMLDOMSelection) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515055 getQualifiedItem Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515058 getResponseHeader Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* aa515075 hasChildNodes Method (Header: Msxml2.h, Msxml2.idl.) */
/* aa515077 hasFeature Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms882815 implementation Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms882858 indent Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms882873 input Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms882875 insertBefore Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms882876 insertData Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884605 ISAXAttributes::getIndexFromName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884606 ISAXAttributes::getIndexFromQName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884607 ISAXAttributes::getLength Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884608 ISAXAttributes::getLocalName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884609 ISAXAttributes::getName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884610 ISAXAttributes::getQName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884613 ISAXAttributes::getType Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884611 ISAXAttributes::getTypeFromName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884612 ISAXAttributes::getTypeFromQName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884614 ISAXAttributes::getURI Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884617 ISAXAttributes::getValue Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884615 ISAXAttributes::getValueFromName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884616 ISAXAttributes::getValueFromQName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms884619 ISAXContentHandler::characters Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885122 ISAXContentHandler::endDocument Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885225 ISAXContentHandler::endElement Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885233 ISAXContentHandler::endPrefixMapping Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885241 ISAXContentHandler::ignorableWhitespace Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885252 ISAXContentHandler::processingInstruction Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885259 ISAXContentHandler::putDocumentLocator Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885268 ISAXContentHandler::skippedEntity Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885277 ISAXContentHandler::startDocument Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885287 ISAXContentHandler::startElement Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885291 ISAXContentHandler::startPrefixMapping Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885297 ISAXDeclHandler::attributeDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885302 ISAXDeclHandler::elementDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885304 ISAXDeclHandler::externalEntityDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885310 ISAXDeclHandler::internalEntityDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885329 ISAXDTDHandler::notationDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885338 ISAXDTDHandler::unparsedEntityDecl Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885348 ISAXEntityResolver::resolveEntity Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885356 ISAXErrorHandler::error Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885365 ISAXErrorHandler::fatalError Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885371 ISAXErrorHandler::ignorableWarning Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885384 ISAXLexicalHandler::comment Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885393 ISAXLexicalHandler::endCDATA Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885400 ISAXLexicalHandler::endDTD Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885408 ISAXLexicalHandler::endEntity Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885428 ISAXLexicalHandler::startCDATA Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885437 ISAXLexicalHandler::startDTD Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885446 ISAXLexicalHandler::startEntity Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885459 ISAXLocator::getColumnNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885463 ISAXLocator::getLineNumber Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885470 ISAXLocator::getPublicId Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885479 ISAXLocator::getSystemId Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885492 ISAXXMLFilter::getParent Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885506 ISAXXMLFilter::putParent Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885514 ISAXXMLReader::getBaseURL Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885592 ISAXXMLReader::getContentHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885696 ISAXXMLReader::getDTDHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885764 ISAXXMLReader::getEntityResolver Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885832 ISAXXMLReader::getErrorHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885845 ISAXXMLReader::getFeature Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885855 ISAXXMLReader::getProperty Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885868 ISAXXMLReader::getSecureBaseURL Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885896 ISAXXMLReader::parse Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885909 ISAXXMLReader::parseURL Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885922 ISAXXMLReader::putBaseURL Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885928 ISAXXMLReader::putContentHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885941 ISAXXMLReader::putDTDHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885950 ISAXXMLReader::putEntityResolver Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885961 ISAXXMLReader::putErrorHandler Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885972 ISAXXMLReader::putFeature Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms885985 ISAXXMLReader::putProperty Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms886006 ISAXXMLReader::putSecureBaseURL Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms890859 item Method (IXMLDOMNamedNodeMap) (Header: Msxml2.h, Msxml2.idl.) */
/* ms890866 item Method (IXMLDOMNodeList) (Header: Msxml2.h, Msxml2.idl.) */
/* ms891739 lastChild Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892323 length Property (IXMLDOMCharacterData) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892324 length Property (IXMLDOMNamedNodeMap) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892325 length Property (IXMLDOMNodeList) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892326 length Property (XMLSchemaCache/IXMLSchemaCollection) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892329 line Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892328 linepos Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892330 load Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892337 loadXML Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892343 matches Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892357 name Property (IXMLDOMAttribute) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892358 name Property (IXMLDOMDocumentType) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892406 namespaces Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892429 namespaceURI Property (IXMLDOMNode) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892438 namespaceURI Property (XMLSchemaCache/IXMLSchemaCollection) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892452 nextNode Method (IXMLDOMNamedNodeMap) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892462 nextNode Method (IXMLDOMNodeList) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892468 nextSibling Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892563 nodeFromID Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892572 nodeName Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892577 nodeType Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892576 nodeTypedValue Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892578 nodeTypeString Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892579 nodeValue Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892580 normalize Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892582 notationName Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892583 notations Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892605 omitXMLDeclaration Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892606 ondataavailable Event (Header: Msxml2.h, Msxml2.idl.) */
/* ms892607 ondataavailable Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892608 onreadystatechange Event (Header: Msxml2.h, Msxml2.idl.) */
/* ms892609 onreadystatechange Property (DOMDocument) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892610 onreadystatechange Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892611 ontransformnode Event (Header: Msxml2.h, Msxml2.idl.) */
/* ms892612 ontransformnode Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892613 open Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892615 output Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892616 output Property (XML SAX) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892618 ownerDocument Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892621 parentNode Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892622 parsed Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892623 parseError Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892627 peekNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892631 prefix Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892632 preserveWhiteSpace Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892633 previousSibling Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892637 publicId Property (IXMLDOMEntity) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892638 publicId Property (IXMLDOMNotation) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892645 readyState Property (DOMDocument) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892646 readyState Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892647 reason Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms892655 remove Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892650 removeAll Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892651 removeAttribute Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892652 removeAttribute Method (XML SAX) (Header: Msxml2.h, Msxml2.idl.) */
/* ms892653 removeAttributeNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892654 removeChild Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892656 removeNamedItem Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892657 removeNext Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892658 removeQualifiedItem Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892659 replaceChild Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms892660 replaceData Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893262 reset Method (IXMLDOMNamedNodeMap) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893268 reset Method (IXMLDOMNodeList) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893273 resolveExternals Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms893279 responseBody Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893286 responseStream Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893295 responseText Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893299 responseXML Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893304 resume Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893443 save Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893448 schemas Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms893450 selectNodes Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893451 selectSingleNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893452 send Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893454 setAttribute Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893455 setAttribute Method (XML SAX) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893456 setAttributeNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893457 setAttributes Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893459 setLocalName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893460 setNamedItem Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893462 setProperty Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893464 setQName Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893465 setRequestHeader Method (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms893466 setStartMode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893467 setType Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893468 setURI Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms893469 setValue Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms895354 specified Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms895592 splitText Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms895975 srcText Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms895976 standalone Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms896205 status Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896213 statusText Property (IXMLHTTPRequest) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896450 substringData Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896469 suspend Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896479 systemId Property (IXMLDOMEntity) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896480 systemId Property (IXMLDOMNotation) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896483 tagName Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms896484 target Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms896485 text Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms896487 transformNode Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896488 transformNodeToObject Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896497 uniqueID Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896501 url Property (DOMDocument) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896502 url Property (IXMLDOMParseError) (Header: Msxml2.h, Msxml2.idl.) */
/* ms896503 validate Method (Header: Msxml2.h, Msxml2.idl.) */
/* ms896504 validateOnParse Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms896505 value Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms897185 version Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms897200 XML DOM Enumerated Constants (Header: Msxml2.h, Msxml2.idl.) */
/* ms897205 xml Property (Header: Msxml2.h, Msxml2.idl.) */
/* ms897206 XMLSchemaCache/IXMLDOMSchemaCollection (Header: Msxml2.h, Msxml2.idl.) */

/* ------------------------------------------------------------------
 * Book surface: msxml (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862736 &lt;xsl:preserve-space&gt; and &lt;xsl:strip-space&gt; Example */
/* ms862073 Accessing and Outputting Attributes */
/* ms862080 Advanced XSLT Functionality */
/* ms862091 Authoring Match Patterns */
/* ms862092 Authoring Well-Formed HTML */
/* ms863695 Axes */
/* ms862096 Best Practices for DOM */
/* ms862097 Best Practices for SAX */
/* ms863866 boolean Function */
/* ms863867 Boolean Functions */
/* ms862099 Boolean, Comparison, and Set Expressions */
/* ms862100 Built-in Templates */
/* ms863873 ceiling Function */
/* ms862105 Choosing Between SAX and DOM */
/* ms863919 Collections */
/* ms863925 Comparisons */
/* ms863927 concat Function */
/* ms862122 Conditional Templates */
/* ms863941 contains Function */
/* ms862125 Controlling White Space with &lt;xsl:text&gt; */
/* ms862123 Controlling White Space with the DOM */
/* ms862124 Controlling White Space with XSLT */
/* ms864381 count Function */
/* ms862126 Creating a Comma-Separated List of Items */
/* ms862130 Creating a Table of Contents */
/* ms862128 Creating and Populating an HTML Template */
/* ms862131 Creating CDATA Sections */
/* ms864405 current Function */
/* ms862134 Debugging a Style Sheet */
/* ms862165 Defining the DOM Context for XPath Expressions */
/* ms862167 Defining the XSLT Context for XPath Expressions */
/* ms864434 document Function */
/* ms862142 Effects of White Space in the Style Sheet */
/* ms864456 element-available Function */
/* ms862151 Exploring XSLT Capabilities */
/* ms862152 Expressions */
/* aa514951 false Function */
/* aa514981 Filters and Filter Patterns */
/* aa514988 floor Function */
/* aa514996 format-number Function */
/* aa515011 function-available Function */
/* ms862154 Fundamentals of Events-Based Parsing */
/* aa515014 generate-id Function */
/* ms862155 Generating More Sophisticated XML Output */
/* ms862157 Getting Started with SAX2 */
/* ms862158 Getting Started with XSLT */
/* ms862160 Handling a Remote Procedural Call that Returns 10 MB of Data */
/* ms862163 Handling Documents and Irregular Data */
/* ms862166 Handling White Space */
/* aa515573 id Function */
/* ms862168 Implementations of XSLT */
/* ms862173 Introduction to the Syntax of XPath */
/* ms891733 IXMLHTTPRequest Members */
/* ms891734 IXMLParseError Error Messages */
/* ms891736 IXTLRuntime Members */
/* ms862175 JumpStart for Creating a SAX2 Application */
/* ms891737 key Function */
/* ms891738 lang Function */
/* ms891740 last Function */
/* ms862469 Limitations of SAX */
/* ms892339 local-name Function */
/* ms892340 Location Path Examples */
/* ms892341 Location Paths */
/* ms892342 Location Steps */
/* ms862526 Microsoft SAX2 COM Implementation */
/* ms892353 msxsl:script Element */
/* ms892356 name Function */
/* ms892423 namespace-uri Function */
/* ms862568 NaN Values */
/* ms862575 NASDAQ Level II Client */
/* ms892575 Node Tests */
/* ms892573 node-set Function */
/* ms892574 Node-Set Functions */
/* ms892581 normalize-space Function */
/* ms892584 not Function */
/* ms892586 number Function */
/* ms892587 Number Functions */
/* ms892614 Operators and Special Characters */
/* ms862669 Overriding &lt;xsl:preserve-space&gt; and &lt;xsl:strip-space&gt; */
/* ms862671 Patterns */
/* ms862672 Placing a List of Items into a Grid */
/* ms892628 position Function */
/* ms892629 Predicates */
/* ms862675 preserveWhiteSpace Property and HTML */
/* ms862676 Preserving and Stripping White Space */
/* ms862679 Qualified Names */
/* ms862682 Release Notes: Handling White Space with the MSXML Processor */
/* ms893312 round Function */
/* ms893441 Sample Data */
/* aa519287 Sample SaxContentHandlerImpl Code */
/* ms893447 SAX2 C++ Common Notices */
/* ms862689 SAX2 Developer Guide */
/* ms862690 SAX2 Implementation Examples */
/* ms862691 Scanning for Part Availability */
/* ms862692 Scanning for Relevant News */
/* ms893461 Set Operations */
/* ms862705 Sorting XML */
/* ms896178 starts-with Function */
/* ms897395 Step 1: Creating the Header File */
/* ms897399 Step 1: Creating the Sales.xml File */
/* ms897396 Step 2: Creating the MyContent Class */
/* ms897400 Step 2: Matching Patterns */
/* ms897397 Step 3: Creating the Main Program */
/* ms897401 Step 3: Looping Through Data */
/* ms897402 Step 4: Adding Conditional Statements */
/* ms897403 Step 5: Adding Other Documents */
/* ms896395 string Function (XML Query Language) */
/* ms896403 String Functions */
/* ms896411 string-length Function */
/* ms896457 substring Function */
/* ms896428 substring-after Function */
/* ms896441 substring-before Function */
/* ms896465 sum Function */
/* ms896481 system-property Function */
/* ms896489 translate Function */
/* ms862715 Translating Between Schemas */
/* ms896491 true Function */
/* ms897404 Tutorial: Getting Started with XSLT */
/* ms897398 Tutorial: JumpStart for Creating a SAX2 Application with C++ */
/* ms896498 unparsed-entity-uri Function */
/* ms862723 Using the Normalize-space() Function */
/* ms862724 Using Threads with XML for Windows CE */
/* ms862726 What is White Space? */
/* ms897385 XML Core Services and Document Object Model */
/* ms862728 XML Core Services Registry Settings */
/* aa513817 XML DOM Application Development */
/* ms897201 XML DOM Error Messages */
/* aa513822 XML DOM Events */
/* aa513825 XML DOM Methods */
/* aa513827 XML DOM Migration */
/* aa513829 XML DOM Objects/Interfaces */
/* aa513831 XML DOM Properties */
/* aa513832 XML DOM Reference */
/* aa513834 XML DOM Samples */
/* ms862729 XML DOM Security */
/* aa513821 XML Error Messages */
/* ms862730 XML for Windows CE */
/* ms897386 XML HTTP */
/* aa513835 XML HTTP Methods */
/* aa513838 XML HTTP Objects/Interfaces */
/* aa513839 XML HTTP Properties */
/* aa513841 XML HTTP Reference */
/* ms897387 XML Minimal Parser */
/* aa513843 XML Minimal Parser Application Development */
/* ms897202 XML Minimal Parser Interfaces */
/* aa513848 XML Minimal Parser Migration */
/* ms897203 XML Minimal Parser Reference */
/* ms862731 XML Minimal Parser Registry Settings */
/* aa513849 XML Minimal Parser Samples */
/* ms897388 XML OS Design Development */
/* ms862732 XML Parser Architecture for Windows CE */
/* ms897389 XML Query Language (XQL) */
/* ms897390 XML SAX */
/* ms862733 XML SAX Application Development */
/* aa513852 XML SAX Interfaces */
/* aa513857 XML SAX Migration */
/* aa513860 XML SAX Reference */
/* aa513862 XML SAX Samples */
/* ms897391 XML Stylesheet Language Transformations (XSLT) */
/* ms862734 XPath */
/* ms897207 XPath Examples */
/* ms897208 XPath Functions */
/* ms897209 XPath Syntax */
/* ms862735 XQL Application Development */
/* ms897210 XQL Error Messages */
/* aa513867 XQL Migration */
/* aa513864 XQL Reference */
/* aa513868 XQL Samples */
/* ms897211 xsl:apply-imports Element */
/* ms897212 xsl:apply-templates Element */
/* ms897213 xsl:attribute Element */
/* ms897214 xsl:attribute-set Element */
/* ms897215 xsl:call-template Element */
/* ms897216 xsl:choose Element */
/* ms897217 xsl:comment Element */
/* ms897218 xsl:copy Element */
/* ms897219 xsl:copy-of Element */
/* ms897220 xsl:decimal-format Element */
/* ms897221 xsl:element Element */
/* ms897223 xsl:fallback Element */
/* ms897224 xsl:for-each Element */
/* ms897225 xsl:if Element */
/* ms897226 xsl:import Element */
/* ms897227 xsl:include Element */
/* ms897228 xsl:key Element */
/* ms897229 xsl:message Element */
/* ms897230 xsl:namespace-alias Element */
/* ms897231 xsl:number Element */
/* ms897232 xsl:otherwise Element */
/* ms897233 xsl:output Element */
/* ms897234 xsl:param Element */
/* ms897347 xsl:preserve-space Element */
/* ms897354 xsl:processing-instruction Element */
/* ms897356 xsl:sort Element */
/* ms897357 xsl:strip-space Element */
/* ms897359 xsl:stylesheet Element */
/* ms897360 xsl:template Element */
/* ms897362 xsl:text Element */
/* ms897363 xsl:transform Element */
/* ms897364 xsl:value-of Element */
/* ms897365 xsl:variable Element */
/* ms897366 xsl:when Element */
/* ms897367 xsl:with-param Element */
/* ms862737 XSLT and XPath Conformance Notes */
/* ms897392 XSLT Application Development */
/* ms862738 XSLT Developer Guide */
/* aa513870 XSLT Elements */
/* ms897361 XSLT Error Messages */
/* aa513874 XSLT Functions */
/* ms862739 XSLT Fundamentals */
/* aa513878 XSLT Interfaces */
/* aa513880 XSLT Methods */
/* aa513884 XSLT Migration */
/* aa513887 XSLT Properties */
/* aa513889 XSLT Reference */
/* aa513268 XSLT Registry Settings */
/* aa513892 XSLT Samples */
/* aa513561 XSLT Security */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSXML2_H */
