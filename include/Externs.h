/* Externs.h -- NDIS miniport driver-supplied entry points
 * (record-only).
 *
 * Source pages: Network Driver Reference rows printing
 * "Header: Externs.h" (20 pages).  These Miniport* functions are
 * implemented by the miniport driver and called by NDIS, not
 * imported; the pages document the required prototypes (records
 * below; ten pages print signatures, ten print prose only).
 * See docs/inventory.md M78c.
 */

#ifndef AKARI_EXTERNS_H
#define AKARI_EXTERNS_H

/* --- Recorded prototypes (driver-supplied; not imports). ------- */
/* "MiniportCancelSendPackets" (aa447841): `VOID MiniportCancelSendPackets( NDIS_HANDLE MiniportAdapterContext,ULONG_PTRCancelId)` */
/* "MiniportCheckForHang" (aa447842): `BOOLEAN MiniportCheckForHang(NDIS_HANDLEMiniportAdapterContext)` */
/* "MiniportHalt" (aa447845): `VOID MiniportHalt(NDIS_HANDLEMiniportAdapterContext)` */
/* "MiniportHandleInterrupt" (aa447846): `VOID MiniportHandleInterrupt( NDIS_HANDLE MiniportAdapterContext)` */
/* "MiniportInitialize" (aa447847): `NDIS_STATUS MiniportInitialize( PNDIS_STATUSOpenErrorStatus,PUINTSelectedMediumIndex,PNDIS_MEDIUMMediumArray,UINTMediumArraySize,NDIS_HANDLEMiniportAdapterHandle,NDIS_HANDLEWrapperConfigurationContext)` */
/* "MiniportSendPackets" (aa447854): `VOID MiniportSendPackets( NDIS_HANDLEMiniportAdapterContext, PPNDIS_PACKET PacketArray, UINTNumberOfPackets)` */
/* "MiniportSynchronizeISR" (aa447857): `BOOLEAN MiniportSynchronizeISR( PVOIDSynchronizeContext)` */
/* "MiniportTimer" (aa447858): `VOID MiniportTimer( PVOIDSystemSpecific1,PVOIDFunctionContext,PVOIDSystemSpecific2,PVOIDSystemSpecific3)` */
/* "MiniportTransferData" (aa447859): `NDIS_STATUS MiniportTransferData(PNDIS_PACKETPacket,PUINTBytesTransferred,NDIS_HANDLEMiniportAdapterContext,NDIS_HANDLEMiniportReceiveContext,UINTByteOffset,UINTBytesToTransfer)` */
/* "MiniportWanSend" (aa447860): `NDIS_STATUS MiniportWanSend( NDIS_HANDLE MiniportAdapterContext, NDIS_HANDLE NdisLinkHandle, PNDIS_WAN_PACKET WanPacket)` */

/* Pages printing no signature (prose descriptions only): MiniportDisableInterrupt, MiniportEnableInterrupt, MiniportISR, MiniportQueryInformation, MiniportReconfigure, MiniportReset, MiniportReturnPacket, MiniportSend, MiniportSetInformation, MiniportShutdown. */

#endif /* AKARI_EXTERNS_H */
